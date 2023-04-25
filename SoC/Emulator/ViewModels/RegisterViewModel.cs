using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Channels;
using System.Threading.Tasks;

namespace Emulator.ViewModels
{
	internal class RegisterViewModel : BaseViewModel
	{
		public string Name { get; set; }

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

		public RegisterViewModel(string name)
		{
			Name = name;
			Value = 0;
		}

		public override string ToString()
		{
			return String.Format("{0}: {1:X8}", Name, Value);
		}
	}
}
