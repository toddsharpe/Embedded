using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Emulator.ViewModels
{
	internal class MainViewModel : BaseViewModel, ILoadable
	{
		private static string fpgaMem = "..\\..\\..\\..\\..\\build\\SoC\\fpga.mem";

		private SoCViewModel _soc;
		public SoCViewModel SoC
		{
			get => _soc;
			set
			{
				if (_soc == value)
					return;

				_soc = value;
				OnPropertyChanged();
			}
		}

		public RelayCommand StartCommand { get; }
		public RelayCommand PauseCommand { get; }
		public RelayCommand SingleCommand { get; }


		public MainViewModel()
		{
			SoC = new SoCViewModel(fpgaMem);

			StartCommand = new RelayCommand(state => SoC.Start());
			PauseCommand = new RelayCommand(state => SoC.Pause());
			SingleCommand = new RelayCommand(state => SoC.Single());
		}

		public Task LoadAsync()
		{
			return Task.CompletedTask;
		}
	}
}
