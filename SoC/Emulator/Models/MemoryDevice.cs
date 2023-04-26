using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Models
{
	internal abstract class MemoryDevice : BaseViewModel
	{
		public uint BaseAddr { get; }
		public uint Size { get; }

		public MemoryDevice(uint baseAddr, uint size)
		{
			BaseAddr = baseAddr;
			Size = size;
		}

		public bool Enabled(uint addr)
		{
			return ((addr >= BaseAddr) && (addr < BaseAddr + Size));
		}

		public abstract void Write(uint address, uint value, MemorySize size);

		public abstract uint Read(uint address, MemorySize size);

		protected static uint ReadBytes(byte[] memory, uint address, MemorySize size)
		{
			switch (size)
			{
				case MemorySize.Byte:
					return memory[address];

				case MemorySize.HalfWord:
					return BitConverter.ToUInt16(memory, (int)address);

				case MemorySize.Word:
					return BitConverter.ToUInt32(memory, (int)address);

				default:
					throw new Exception();
			}
		}

		protected static void WriteBytes(byte[] memory, uint address, uint value, MemorySize size)
		{
			byte[] bytes;
			switch (size)
			{
				case MemorySize.Byte:
					bytes = new [] { (byte)value };
					break;

				case MemorySize.HalfWord:
					bytes = BitConverter.GetBytes((ushort)value);
					break;

				case MemorySize.Word:
					bytes = BitConverter.GetBytes(value);
					break;

				default:
					throw new Exception();
			}
			bytes.CopyTo(memory, address);
		}
	}
}
