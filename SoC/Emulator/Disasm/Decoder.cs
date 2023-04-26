using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Disasm
{
	internal class Decoder
	{
		public static Instruction Decode(uint instr)
		{
			Instruction parsed = new Instruction();
			parsed.Instr = instr;
			//Instruction
			uint op = instr & 0b1111111;
			if (!Enum.IsDefined(typeof(OpCode), op))
				parsed.OpCode = OpCode.Unknown;
			else
				parsed.OpCode = (OpCode)op;

			//Immediates
			parsed.Uimm = (GetBit(instr, 31) << 31) | (GetBits(instr, 12, 19) << 12);
			parsed.Iimm = (ExtendBit(GetBit(instr, 31), 21) << 11) | GetBits(instr, 20, 11);
			parsed.Simm = (ExtendBit(GetBit(instr, 31), 21) << 11) | GetBits(instr, 25, 6) << 5 | GetBits(instr, 7, 5);
			parsed.Bimm = (ExtendBit(GetBit(instr, 31), 20) << 12) | GetBit(instr, 7) << 11 | GetBits(instr, 25, 6) << 5 | GetBits(instr, 8, 4) << 1;
			parsed.Jimm = (ExtendBit(GetBit(instr, 31), 12) << 20) | GetBits(instr, 12, 8) << 12 | GetBit(instr, 20) << 11 | GetBits(instr, 21, 10) << 1;

			uint bimm2 = ParseBimm2(instr);
			if (parsed.Bimm != bimm2)
				Debugger.Break();

			//Registers
			parsed.Rs1Id = GetBits2(instr, 15, 19);
			parsed.Rs2Id = GetBits2(instr, 20, 24);
			parsed.RdId = GetBits2(instr, 7, 11);

			//Functions
			parsed.Funct3 = GetBits(instr, 12, 3);
			parsed.Funct7 = GetBits(instr, 25, 7);

			return parsed;
		}

		private static uint ParseBimm2(uint instr)
		{
			uint RdId = GetBits2(instr, 7, 11);
			uint funct7 = GetBits(instr, 25, 7);
			uint imm_11 = RdId & 1;
			uint imm_4_1 = RdId >> 1;
			uint imm_10_5 = (uint)(funct7 & ~(1 << 6));
			uint imm_12 = funct7 >> 6;
			uint imm_32_13 = ExtendBit(imm_12, 19);

			return imm_32_13 << 13 | imm_12 << 12 | imm_11 << 11 | imm_10_5 << 5 | imm_4_1 << 1;
		}

		private static uint ExtendBit(uint value, int length)
		{
			if (value == 0)
				return 0;

			while (length > 1)
			{
				value = (value << 1) | 1;
				length--;
			}
			return value;
		}
		
		private static uint GetBit(uint value, int pos)
		{
			int iValue = (int)value;
			int mask = (1 << pos);
			iValue &= mask;
			return (uint)(iValue >> pos);
		}

		//Uses start and stop bits (should have done that in the first place)
		private static uint GetBits2(uint value, int start, int end)
		{
			return GetBits(value, start, (end - start) + 1);
		}

		private static uint GetBits(uint value, int start, int length)
		{
			int iValue = (int)value;
			int mask = (1 << length) - 1;
			mask = mask << start;
			iValue &= mask;
			return (uint)(iValue >> start);
		}
	}
}
