#include "SoC/Basys3.h"

#include <SoC.h>

namespace SoC
{
	Basys3::Basys3() :
		Board(),
		uart(UART)
	{

	}

	void Basys3::Init()
	{
		//Initialize peripherals
		uart.Init();

		//Print welcome
		uart.Printf("Board initialized\r\n");
		uart.Printf("Cycles: 0x%x, Freq: 0x%x\r\n", SOC_BLOCK->cycles, SOC_BLOCK->freq);

		//Set LEDs
		IO_BLOCK->led_display = 0x1234;
		IO_BLOCK->led_bar = 0xFF00;
	}

	void Basys3::Printf(const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		uart.Printf(format, args);
		va_end(args);
	}

	void Basys3::Printf(const char* format, va_list args)
	{
		uart.Printf(format, args);
	}

	void Basys3::Write(const std::string& str)
	{
		uart.Write(str);
	}

	uint32_t Basys3::GetSysClkFreq() const
	{
		return SOC_BLOCK->freq;
	}
}
