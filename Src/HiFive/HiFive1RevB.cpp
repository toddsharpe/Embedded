#include "HiFive/HiFive1RevB.h"
#include "HiFive/Prci.h"

namespace HiFive
{
	HiFive1RevB::HiFive1RevB() :
		Board(),
		uart(UART0)
	{
	}

	void HiFive1RevB::Init()
	{
		//Initialize system clock
		HiFive::Prci::Init(DefaultPrciConfig);

		//Intialize UART
		uart.Init(GetSysClkFreq(), UartDefault);

		LedRed.Init(GpioOutput);
		LedGreen.Init(GpioOutput);
		LedBlue.Init(GpioOutput);
	}

	void HiFive1RevB::Write(const std::string &str)
	{
		uart.Write(str);
	}

	uint32_t HiFive1RevB::GetSysClkFreq() const
	{
		return Prci::GetSysClkFreq();
	}
}
