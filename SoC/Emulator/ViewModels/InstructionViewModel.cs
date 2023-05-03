using Emulator.Disasm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace Emulator.ViewModels
{
	internal class InstructionViewModel : BaseViewModel
	{
		public ulong Address { get; }
		public string BytesString { get; private set; }
		public string InstructionString { get; private set; }

		private Instruction _instr;

		public InstructionViewModel(uint address, uint instr)
		{
			Address = address;
			_instr = Disasm.Decoder.Decode(instr);

			BytesString = BitConverter.ToString(BitConverter.GetBytes(instr).Reverse().ToArray()).Replace('-', ' ');

			InstructionString = Display();
		}

		private string Display()
		{
			switch (_instr.OpCode)
			{
				case OpCode.Branch:
					return String.Format("B:{0}({1},{2}): {3:X8}", (BranchOp)_instr.Funct3, _instr.Rs1Id, _instr.Rs2Id, (uint)(Address + _instr.Bimm));

				default:
					return _instr.ToString();
			}
		}
	}
}
