using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.ViewModels
{
	internal class ContextViewModel : BaseViewModel
	{
		private const uint NUM_REGS = 32;

		public RegisterViewModel PC { get; }
		public RegisterViewModel Instr { get; }
		public List<RegisterViewModel> Registers { get; }
		public List<RegisterViewModel> InternalRegisters { get; }

		public ContextViewModel()
		{
			PC = new RegisterViewModel("PC");
			Instr = new RegisterViewModel("INSTR");
			Registers = new List<RegisterViewModel>
			{
				new RegisterViewModel("x0 (zero)"),
				new RegisterViewModel("x1 (ra)"),
				new RegisterViewModel("x2 (sp)"),
				new RegisterViewModel("x3 (gp)"),
				new RegisterViewModel("x4 (tp)"),
				new RegisterViewModel("x5 (t0)"),
				new RegisterViewModel("x6 (t1)"),
				new RegisterViewModel("x7 (t2)"),
				new RegisterViewModel("x8 (s0)"),
				new RegisterViewModel("x9 (s1)"),
				new RegisterViewModel("x10 (a0)"),
				new RegisterViewModel("x11 (a1)"),
				new RegisterViewModel("x12 (a2)"),
				new RegisterViewModel("x13 (a3)"),
				new RegisterViewModel("x14 (a4)"),
				new RegisterViewModel("x15 (a5)"),
				new RegisterViewModel("x16 (a6)"),
				new RegisterViewModel("x17 (a7)"),
				new RegisterViewModel("x18 (s2)"),
				new RegisterViewModel("x19 (s3)"),
				new RegisterViewModel("x20 (s4)"),
				new RegisterViewModel("x21 (s5)"),
				new RegisterViewModel("x22 (s6)"),
				new RegisterViewModel("x23 (s7)"),
				new RegisterViewModel("x24 (s8)"),
				new RegisterViewModel("x25 (s9)"),
				new RegisterViewModel("x26 (s10)"),
				new RegisterViewModel("x27 (s11)"),
				new RegisterViewModel("x28 (t3)"),
				new RegisterViewModel("x29 (t4)"),
				new RegisterViewModel("x30 (t5)"),
				new RegisterViewModel("x31 (t6)"),
			};
			InternalRegisters = new List<RegisterViewModel> { PC, Instr };
			OnPropertyChanged("Registers");
		}

		public void RollFrame()
		{
			PC.Changed = false;
			Instr.Changed = false;
			foreach (RegisterViewModel reg in Registers)
			{
				reg.Changed = false;
			}
		}

		public void SetReg(uint index, uint value)
		{
			if (index == 0)
				return;

			Registers[(int)index].Value = value;
		}

		public uint GetReg(uint index)
		{
			return Registers[(int)index].Value;
		}
	}
}
