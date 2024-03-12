#include "SoC/Boards/Basys3.h"

#include <SoC.h>

namespace Board
{
	//Peripherals
	SoC::Uart uart(UART);
	
	void Init()
	{
		//Initialize peripherals
		uart.Init();
		Board::Printf("Board initialized\r\n");

		//Set LEDs
		IO_BLOCK->led_display = 0x1234;
		IO_BLOCK->led_bar = 0xFF00;

		//Print welcome
		Board::Printf("    Initialized\r\n");

		//Print clocks
		Board::Printf("Cycles: 0x%x, Freq: 0x%x\r\n", SOC_BLOCK->cycles, SOC_BLOCK->freq);
	}

	void Write(const ReadOnlyBuffer& buffer)
	{
		uart.Write(buffer);
	}

	uint32_t GetSysClkFreq()
	{
		return SOC_BLOCK->freq;
	}
}
