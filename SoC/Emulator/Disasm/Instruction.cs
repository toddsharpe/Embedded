using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Disasm
{
	internal class Instruction
	{
		public OpCode OpCode { get; set; }

		//5 Possible Immediates
		public uint Uimm { get; set; }
		public uint Iimm { get; set; }
		public uint Simm { get; set; }
		public uint Bimm { get; set; }
		public uint Jimm { get; set; }

		//Register selects
		public uint Rs1Id { get; set; }
		public uint Rs2Id { get; set; }
		public uint RdId { get; set; }

		//Function selects
		public uint Funct3 { get; set; }
		public uint Funct7 { get; set; }
	}
}
