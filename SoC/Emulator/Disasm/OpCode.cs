using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Disasm
{
	enum OpCode : uint
	{
		Unknown = 0,
		LUI = 0b0110111,
		AUIPC = 0b0010111,
		JAL = 0b1101111,
		JALR = 0b1100111,
		Branch = 0b1100011,
		Load = 0b0000011,
		Store = 0b0100011,
		ALUimm = 0b0010011,
		ALUreg = 0b0110011,
		SYSTEM = 0b1110011
	}
}
