using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.DirectoryServices;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Emulator.Disasm;
using Emulator.Models;

namespace Emulator.ViewModels
{
	internal class SoCViewModel : BaseViewModel
	{
		//Memory layout constants
		private const uint MEM_START = 0;
		private const uint MEM_SIZE = 0x10000;
		private const uint LED_DISPLAY_START = 0x10000;
		private const uint LED_DISPLAY_SIZE = sizeof(uint);
		private const uint LED_BAR_START = 0x10004;
		private const uint LED_BAR_SIZE = sizeof(uint);
		private const uint SWITCHES_START = 0x10008;
		private const uint SWITCHES_SIZE = sizeof(uint);
		private const uint UART_START = 0x10010;
		private const uint UART_SIZE = sizeof(uint);

		enum BranchOp
		{
			EQ = 0,
			NE = 1,
			LT = 4,
			GE = 5,
			LTU = 6,
			GEU = 7
		};

		//Memory
		public Memory Memory { get; }
		public UartDevice Uart { get; }
		public LedDisplay Display { get; }
		private List<MemoryDevice> _devices;

		//Context
		public ContextViewModel Context { get; }

		//Execution
		private Thread _thread;
		private AutoResetEvent _event;
		private bool _running;

		public SoCViewModel(string memFile)
		{
			Memory = new Memory(MEM_START, MEM_SIZE, memFile);
			Display = new LedDisplay(LED_DISPLAY_START, LED_DISPLAY_SIZE);
			MemoryHole hole = new MemoryHole(LED_BAR_START, LED_BAR_SIZE + SWITCHES_SIZE);
			Uart = new UartDevice(UART_START, UART_SIZE);
			
			_devices = new List<MemoryDevice>
			{
				Memory, Display, hole, Uart
			};

			//Context
			Context = new ContextViewModel();

			_thread = new Thread(Run);
			_thread.Start();
			_event = new AutoResetEvent(false);
		}

		public void Start()
		{
			_running = true;
		}

		public void Pause()
		{
			_running = false;
		}

		public void Single()
		{
			_event.Set();
		}

		private void Run()
		{
			//State
			bool halted = false;

			const int clk_freq = 1024;

			while (!halted)
			{
				if (!_running)
					_event.WaitOne();
				Context.RollFrame();

				//Fetch + Decode
				Context.Instr.Value = MemRead(Context.PC.Value, MemorySize.Word);
				Instruction instr = Disasm.Decoder.Decode(Context.Instr.Value);

				//Derrived data
				bool isA = (instr.Funct7 & (1 << 5)) != 0;
				bool isSub = ((instr.Funct7 & (1 << 5)) & (Context.Instr.Value & (1 << 5))) != 0;
				AluOp op = AluOpSelect(instr.Funct3, isSub, isA);

				uint in1 = Context.GetReg(instr.Rs1Id);
				uint in2 = (instr.OpCode == OpCode.ALUreg || instr.OpCode == OpCode.Branch) ? Context.GetReg(instr.Rs2Id) : instr.Iimm;

				Alu alu = new Alu(op, (int)in1, (int)in2);

				//Execute
				switch (instr.OpCode)
				{
					case OpCode.AUIPC:
						
						Context.SetReg(instr.RdId, Context.PC.Value + instr.Uimm);
						Context.PC.Value += 4;
						break;

					case OpCode.ALUimm:
						Context.SetReg(instr.RdId, (uint)alu.Result);
						Context.PC.Value += 4;
						break;

					case OpCode.ALUreg:
						Context.SetReg(instr.RdId, (uint)alu.Result);
						Context.PC.Value += 4;
						break;

					case OpCode.JAL:
						Context.SetReg(instr.RdId, Context.PC.Value + 4);
						Context.PC.Value += instr.Jimm;
						break;

					case OpCode.JALR:
						uint saved = Context.GetReg(instr.Rs1Id);
						Context.SetReg(instr.RdId, Context.PC.Value + 4);
						Context.PC.Value = saved + instr.Iimm;
						break;

					case OpCode.Store:
					{
						uint addr = Context.GetReg(instr.Rs1Id) + instr.Simm;
						MemorySize size = (MemorySize)(instr.Funct3 & 0b11);
						MemWrite(addr, Context.GetReg(instr.Rs2Id), size);
						Context.PC.Value += 4;
					}
						break;

					case OpCode.Load:
					{
						uint addr = Context.GetReg(instr.Rs1Id) + instr.Iimm;
						MemorySize size = (MemorySize)(instr.Funct3 & 0b11);
						bool signExtend = (instr.Funct3 & 0b100) != 0;
						uint loaded = MemRead(addr, size);
						uint extended = SignExtend(loaded, size, signExtend);
						Context.SetReg(instr.RdId, extended);
						Context.PC.Value += 4;
					}
						break;

					case OpCode.LUI:
						Context.SetReg(instr.RdId, instr.Uimm);
						Context.PC.Value += 4;
						break;

					case OpCode.Branch:
						bool takeBranch = TakeBranch((BranchOp)instr.Funct3, alu.EQ, alu.LT, alu.LTU);
						if (takeBranch)
							Context.PC.Value += instr.Bimm;
						else
							Context.PC.Value += 4;
						break;

					default:
						throw new Exception();
				}

				Thread.Sleep(TimeSpan.FromMicroseconds(1000000.0 / clk_freq));
			}
		}

		private AluOp AluOpSelect(uint func3, bool isSub, bool isA)
		{
			switch (func3)
			{
				case 0b000:
					return isSub ? AluOp.SUB : AluOp.ADD;
				case 0b001:
					return AluOp.SLL;
				case 0b010:
					return AluOp.SLT;
				case 0b011:
					return AluOp.SLTU;
				case 0b100:
					return AluOp.XOR;
				case 0b101:
					return isA ? AluOp.SRA : AluOp.SRL;
				case 0b110:
					return AluOp.OR;
				case 0b111:
					return AluOp.AND;
				default:
					throw new Exception();
			}
		}

		private bool TakeBranch(BranchOp op, bool EQ, bool LT, bool LTU)
		{
			switch (op)
			{
				case BranchOp.EQ:
					return EQ;
				case BranchOp.NE:
					return !EQ;
				case BranchOp.LT:
					return LT;
				case BranchOp.GE:
					return !LT;
				case BranchOp.LTU:
					return LTU;
				case BranchOp.GEU:
					return !LTU;
				default:
					throw new Exception();
			}
		}

		private uint SignExtend(uint value, MemorySize size, bool extend)
		{
			if (!extend)
				return value;
			
			switch (size)
			{
				case MemorySize.Byte:
					return (uint)(sbyte)value;

				case MemorySize.HalfWord:
					return (uint)(short)value;

				case MemorySize.Word:
					return value;

				default:
					throw new Exception();
			}
		}

		//TODO: find a way to put in read size?
		private uint MemRead(uint address, MemorySize size)
		{
			MemoryDevice device = _devices.Single(i => i.Enabled(address));
			return device.Read(address, size);
		}

		private void MemWrite(uint address, uint value, MemorySize size)
		{
			MemoryDevice device = _devices.Single(i => i.Enabled(address));

			device.Write(address, value, size);
		}
	}
}
