using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.DirectoryServices;
using System.IO;
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

		private const uint DEVICE_START = 0x100000;
		private const uint SOC_BLOCK = DEVICE_START;
		private const uint IO_BLOCK = DEVICE_START + 0x100;
		private const uint GPIO1 = DEVICE_START + 0x200;
		private const uint UART = DEVICE_START + 0x300;
		private const uint SPI1 = DEVICE_START + 0x400;

		//Memory
		public List<InstructionViewModel> Instructions { get; }
		public Memory Memory { get; }
		public SocBlock Soc { get; }
		public IoBlock Io { get; }
		public UartDevice Uart { get; }
		public IoBlock Display { get; }
		private List<MemoryDevice> _devices;
		public BinaryReader Reader { get; }

		//Context
		public ContextViewModel Context { get; }
		private bool _halted;
		public bool Halted
		{
			get => _halted;
			set
			{
				if (_halted == value)
					return;

				_halted = value;
				OnPropertyChanged();
			}
		}

		//Execution
		private Thread _thread;
		private AutoResetEvent _event;
		private bool _running;

		public SoCViewModel(string memFile)
		{
			//Read file
			uint[] words = File.ReadAllLines(memFile).Select(i => uint.Parse(i, System.Globalization.NumberStyles.HexNumber)).ToArray();

			//Memory devices
			Memory = new Memory(MEM_START, MEM_SIZE, words);
			Soc = new SocBlock(SOC_BLOCK);
			Io = new IoBlock(IO_BLOCK);
			Uart = new UartDevice(UART);
			_devices = new List<MemoryDevice>
			{
				Memory, Soc, Io, Uart
			};
			Reader = new BinaryReader(Memory.AsStream());
			OnPropertyChanged("Reader");

			//Instructions
			Instructions = words.Select((v, i) => new InstructionViewModel((uint)(i * sizeof(int)), v)).ToList();

			//Context
			Context = new ContextViewModel();
			Halted = false;

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
			const int clk_freq = 0x100000;
			Soc.SetFreq(clk_freq);

			while (!Halted)
			{
				if (!_running)
					_event.WaitOne();
				Context.RollFrame();

				//Fetch + Decode
				Context.Instr.Value = MemRead(Context.PC.Value, MemorySize.Word);
				Instruction instr = Disasm.Decoder.Decode(Context.Instr.Value);

				//Derrived data
				AluOp op = instr.GetAluOp();

				//Decoding asserts (would catch M instruction).
				if (instr.OpCode == OpCode.ALUreg)
				{
					switch (op)
					{
						case AluOp.AND:
						case AluOp.SLL:
						case AluOp.SLT:
						case AluOp.SLTU:
						case AluOp.XOR:
						case AluOp.SRL:
						case AluOp.OR:
							Debug.Assert(instr.Funct7 == 0);
							break;

						case AluOp.SUB:
							Debug.Assert(instr.Funct7 == (1 << 5));
							break;

					}
				}

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
						uint target = Context.PC.Value + instr.Bimm;
						if (takeBranch)
							Context.PC.Value += instr.Bimm;
						else
							Context.PC.Value += 4;
						break;

					case OpCode.SYSTEM:
						Halted = true;
						break;

					default:
						throw new Exception();
				}

				Thread.Sleep(TimeSpan.FromMicroseconds(1000000.0 / clk_freq));
				Soc.AddCycles(2);
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
