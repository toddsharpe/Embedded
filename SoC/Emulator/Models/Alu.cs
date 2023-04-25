using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Models
{
	internal class Alu
	{
		public bool LT { get; }
		public bool LTU { get; }
		public bool EQ { get; }
		public int Result { get; }

		public Alu(AluOp op, int in1, int in2)
		{
			LT = in1 < in2;
			LTU = (uint)in1 < (uint)in2;
			EQ = in1 == in2;
			Result = Calc(op, in1, in2);
		}

		private int Calc(AluOp op, int in1, int in2)
		{
			switch (op)
			{
				case AluOp.ADD:
					return in1 + in2;
				case AluOp.SUB:
					return in1 - in2;
				case AluOp.SLL:
					return in1 << in2;
				case AluOp.SLT:
					return LT ? 1 : 0;
				case AluOp.SLTU:
					return LTU ? 1 : 0;
				case AluOp.XOR:
					return in1 ^ in2;
				case AluOp.SRL:
					return in1 >>> in2;
				case AluOp.SRA:
					return in1 >> in2;
				case AluOp.OR:
					return in2 | in2;
				case AluOp.AND:
					return in1 & in2;
				default:
					throw new Exception();
			}
		}
	}
}
