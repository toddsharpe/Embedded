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
		
		public Memory(uint baseAddr, uint size, uint[] words) : base(baseAddr, size)
		{
			_memory = new byte[size];

			//Load file
			for (int i = 0; i < words.Length; i++)
			{
				BitConverter.GetBytes(words[i]).CopyTo(_memory, i * sizeof(uint));
			}

			//Fill rest of memory with a well known value for debugging
			for (int i = words.Length * 4; i < _memory.Length; i++)
			{
				if (_memory[i] == 0)
					_memory[i] = 0xcc;
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
