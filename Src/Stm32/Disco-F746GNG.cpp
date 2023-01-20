#include "Stm32/Disco-F746GNG.h"

#include <stm32f746xx.h>

namespace Stm32
{
	DiscoF746GNG::DiscoF746GNG() :
		Board(),
		rcc(16'000'000, 25'000'000),
		uart(USART1)
	{

	}

	void DiscoF746GNG::Init()
	{
		//Initialize peripherals
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
		__DSB();
		
		//Initialize system clock
		Pll::Init(PllConfig200MHz);
		SystemClock::Init(SysClock200MHz);

		//Initialize peripherals
		GpioPin<Port_A, 9> uart1_tx;
		uart1_tx.Init(GpioUart1);
		GpioPin<Port_B, 7> uart1_rx;
		uart1_rx.Init(GpioUart1);
		uart.Init(rcc.GetPClk2Freq(), UartDefault);
		uart.EnableInterrupt(USART_CR1_RXNEIE);

		//Print welcome
		uart.Printf("Board initialized\r\n");

		//Print clocks
		RccClocks clocks = {};
		rcc.GetSystemClocksFreq(clocks);
		uart.Printf("-SysClkFreq: %d\r\n", clocks.SysClkFreq);
		uart.Printf("-HClkFreq: %d\r\n", clocks.HClkFreq);
		uart.Printf("-PClk1Freq: %d\r\n", clocks.PClk1Freq);
		uart.Printf("-PClk2Freq: %d\r\n", clocks.PClk2Freq);
	}

	void DiscoF746GNG::Printf(const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		uart.Printf(format, args);
		va_end(args);
	}

	void DiscoF746GNG::Printf(const char* format, va_list args)
	{
		uart.Printf(format, args);
	}

	void DiscoF746GNG::Write(const std::string& str)
	{
		uart.Write(str);
	}

	uint32_t DiscoF746GNG::GetSysClkFreq() const
	{
		return rcc.GetSysClkFreq();
	}
}
