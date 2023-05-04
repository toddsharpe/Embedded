using Emulator.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Models
{
	internal class SocBlock : MemoryDevice
	{
		public List<RegisterViewModel> Values { get; }

		public SocBlock(uint baseAddr) : base(baseAddr, 2 * sizeof(int))
		{
			Values = new List<RegisterViewModel>
			{
				new RegisterViewModel("Cycles"),
				new RegisterViewModel("Freq"),
			};
		}

		public void AddCycles(int delta)
		{
			uint current = Read(BaseAddr, MemorySize.Word);
			current += (uint)delta;
			Write(BaseAddr, current, MemorySize.Word);
		}
		
		public void SetFreq(int freq)
		{
			Write(BaseAddr + sizeof(int), (uint)freq, MemorySize.Word);
		}

		public override uint Read(uint address, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();

			int index = (int)(address - BaseAddr) / sizeof(int);
			RegisterViewModel model = Values[index];
			byte[] bytes = BitConverter.GetBytes(model.Value);
			return ReadBytes(bytes, address % 4, size);
		}

		public override void Write(uint address, uint value, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();

			int index = (int)(address - BaseAddr) / sizeof(int);
			RegisterViewModel model = Values[index];
			byte[] bytes = BitConverter.GetBytes(model.Value);
			WriteBytes(bytes, address % 4, value, size);
			model.Value = BitConverter.ToUInt32(bytes);
		}
	}
}
