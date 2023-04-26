using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Models
{
	internal class UartDevice : MemoryDevice
	{
		private string _log;
		public string Log
		{
			get => _log;
			set
			{
				if (_log == value) return;

				_log = value;
				OnPropertyChanged();
			}
		}
		
		public UartDevice(uint baseAddr, uint size) : base(baseAddr, size)
		{
			_log = string.Empty;
		}

		public override uint Read(uint address, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();
			
			//Always report as idle
			return (1 << 32);
		}

		public override void Write(uint address, uint value, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();

			Log += (char)(value & 0xFF);
		}
	}
}
