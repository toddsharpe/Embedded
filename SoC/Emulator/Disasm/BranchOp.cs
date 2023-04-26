using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Disasm
{
	internal enum BranchOp
	{
		EQ = 0,
		NE = 1,
		LT = 4,
		GE = 5,
		LTU = 6,
		GEU = 7
	};
}
