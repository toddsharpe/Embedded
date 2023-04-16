using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Channels;
using System.Threading.Tasks;

namespace Emulator.ViewModels
{
	[Flags]
	internal enum Access
	{
		Read = 1,
		Write = 2,
		ReadWrite = Read | Write
	}
	
	internal class RegisterViewModel : BaseViewModel
	{
		public string Name { get; }

		private uint _value;
		public uint Value
		{
			get
			{
				return _value;
			}
			set
			{
				if (_value == value)
				{
					Changed = false;
					return;
				}
				
				_value = value;
				OnPropertyChanged();
				Changed = true;
			}
		}

		public Access Access { get; }

		public RegisterViewModel(string name, Access access = Access.ReadWrite)
		{
			Name = name;
			Value = 0;
			Access = access;
		}

		public override string ToString()
		{
			return String.Format("{0}: {1:X8}", Name, Value);
		}
	}
}
