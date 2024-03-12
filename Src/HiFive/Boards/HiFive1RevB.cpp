#include "HiFive/Boards/HiFive1RevB.h"
#include "HiFive/Prci.h"

using namespace HiFive;

namespace Board
{
	//Peripherals
	Uart uart(UART0);
	GpioPin LedRed(22);
	GpioPin LedGreen(19);
	GpioPin LedBlue(21);

	void Init()
	{
		//Initialize system clock
		Prci::Init(DefaultPrciConfig);

		//Intialize UART
		uart.Init(GetSysClkFreq(), UartDefault);

		LedRed.Init(GpioOutput);
		LedGreen.Init(GpioOutput);
		LedBlue.Init(GpioOutput);

		//Print clocks
		Board::Printf("-SysClk: %d\r\n", GetSysClkFreq());
	}

	void Write(const ReadOnlyBuffer& buffer)
	{
		uart.Write(buffer);
	}

	uint32_t GetSysClkFreq()
	{
		return Prci::GetSysClkFreq();
	}
}
