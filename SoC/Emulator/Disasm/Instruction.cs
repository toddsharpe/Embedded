using Emulator.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Disasm
{
	internal class Instruction
	{
		public uint Instr { get; set; }
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

		public AluOp GetAluOp()
		{
			bool instr_5 = (Instr & (1 << 5)) != 0;
			bool func7_5 = (Funct7 & (1 << 5)) != 0;

			switch (Funct3)
			{
				case 0b000:
					return (func7_5 && instr_5) ? AluOp.SUB : AluOp.ADD;
				case 0b001:
					return AluOp.SLL;
				case 0b010:
					return AluOp.SLT;
				case 0b011:
					return AluOp.SLTU;
				case 0b100:
					return AluOp.XOR;
				case 0b101:
					return func7_5 ? AluOp.SRA : AluOp.SRL;
				case 0b110:
					return AluOp.OR;
				case 0b111:
					return AluOp.AND;
				default:
					throw new Exception();
			}
		}

		public override string ToString()
		{
			if (OpCode == OpCode.Branch)
				return String.Format("{0},{1}: {2},{3},{4}", OpCode, (BranchOp)Funct3, RdId, Rs1Id, Rs2Id);
			else
				return String.Format("{0},{1}: {2},{3},{4}", OpCode, GetAluOp(), RdId, Rs1Id, Rs2Id);
		}
	}
}
