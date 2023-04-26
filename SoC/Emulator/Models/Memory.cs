using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Shapes;

namespace Emulator.Models
{
	internal class Memory : MemoryDevice
	{
		private byte[] _memory;
		
		public Memory(uint baseAddr, uint size, string memFile) : base(baseAddr, size)
		{
			_memory = new byte[size];

			//Load file
			string[] lines = File.ReadAllLines(memFile);
			for (int i = 0; i < lines.Length; i++)
			{
				uint value = uint.Parse(lines[i], System.Globalization.NumberStyles.HexNumber);
				BitConverter.GetBytes(value).CopyTo(_memory, i * sizeof(uint));
			}
		}

		public override uint Read(uint address, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();

			return ReadBytes(_memory, address, size);
		}

		public override void Write(uint address, uint value, MemorySize size)
		{
			if (!this.Enabled(address))
				throw new Exception();

			WriteBytes(_memory, address, value, size);
		}
	}
}
