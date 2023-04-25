using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Models
{
	internal class MemoryHole : MemoryDevice
	{
		public MemoryHole(uint baseAddr, uint size) : base(baseAddr, size)
		{

		}

		public override uint Read(uint address, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();

			return 0;
		}

		public override void Write(uint address, uint value, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();
		}
	}
}
