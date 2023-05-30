﻿using Emulator.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.Models
{
	internal class GpioBlock : MemoryDevice
	{
		public List<RegisterViewModel> Values { get; }

		public GpioBlock(uint baseAddr) : base(baseAddr, 3 * sizeof(int))
		{
			Values = new List<RegisterViewModel>
			{
				new RegisterViewModel("Data In"),
				new RegisterViewModel("Data Out"),
				new RegisterViewModel("Dir")
			};
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
