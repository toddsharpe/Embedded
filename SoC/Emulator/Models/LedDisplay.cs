using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Models
{
	internal class LedDisplay : MemoryDevice
	{
		private uint _value;
		public uint Value
		{
			get => _value;
			set
			{
				if (_value == value)
					return;

				_value = value;
				OnPropertyChanged();
			}
		}

		public LedDisplay(uint baseAddr, uint size) : base(baseAddr, size)
		{

		}

		public override uint Read(uint address, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();

			return _value;
		}

		public override void Write(uint address, uint value, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();

			Value = value;
		}
	}
}
