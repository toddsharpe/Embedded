#include "Stm32/Disco-F746GNG.h"

#include <stm32f746xx.h>

namespace Stm32
{
	DiscoF746GNG::DiscoF746GNG() :
		Board(),
		rcc(16'000'000, 25'000'000),
		uart(USART1),
		ltdc(RK043FN48HConfig)
	{

	}

	void DiscoF746GNG::Init()
	{
		//Initialize peripherals
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN);
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);
		__DSB();
		
		//Initialize system clock
		Pll::Init(PllConfig200MHz);
		SystemClock::Init(SysClock200MHz);
		Pll::Init(PllSaiConfig200MHz);

		//Initialize Uart1
		GpioPin<Port_A, 9>::Configure(GpioUart1);
		GpioPin<Port_B, 7>::Configure(GpioUart1);
		uart.Init(rcc.GetPClk2Freq(), UartDefault);

		//Initialize LTDC
		GpioPin<Port_I, 15>::Configure(GpioLtdc14);		//R0
		GpioPin<Port_J, 0>::Configure(GpioLtdc14);		//R1
		GpioPin<Port_J, 1>::Configure(GpioLtdc14);		//R2
		GpioPin<Port_J, 2>::Configure(GpioLtdc14);		//R3
		GpioPin<Port_J, 3>::Configure(GpioLtdc14);		//R4
		GpioPin<Port_J, 4>::Configure(GpioLtdc14);		//R5
		GpioPin<Port_J, 5>::Configure(GpioLtdc14);		//R6
		GpioPin<Port_J, 6>::Configure(GpioLtdc14);		//R7
		GpioPin<Port_J, 7>::Configure(GpioLtdc14);		//G0
		GpioPin<Port_J, 8>::Configure(GpioLtdc14);		//G1
		GpioPin<Port_J, 9>::Configure(GpioLtdc14);		//G2
		GpioPin<Port_J, 10>::Configure(GpioLtdc14);		//G3
		GpioPin<Port_J, 11>::Configure(GpioLtdc14);		//G4
		GpioPin<Port_K, 0>::Configure(GpioLtdc14);		//G5
		GpioPin<Port_K, 1>::Configure(GpioLtdc14);		//G6
		GpioPin<Port_K, 2>::Configure(GpioLtdc14);		//G7
		GpioPin<Port_E, 4>::Configure(GpioLtdc14);		//B0
		GpioPin<Port_J, 13>::Configure(GpioLtdc14);		//B1
		GpioPin<Port_J, 14>::Configure(GpioLtdc14);		//B2
		GpioPin<Port_J, 15>::Configure(GpioLtdc14);		//B3
		GpioPin<Port_G, 12>::Configure(GpioLtdc9);		//B4
		GpioPin<Port_K, 4>::Configure(GpioLtdc14);		//B5
		GpioPin<Port_K, 5>::Configure(GpioLtdc14);		//B6
		GpioPin<Port_K, 6>::Configure(GpioLtdc14);		//B7
		GpioPin<Port_K, 7>::Configure(GpioLtdc14);		//DE
		GpioPin<Port_I, 14>::Configure(GpioLtdc14);		//CLK
		GpioPin<Port_I, 10>::Configure(GpioLtdc14);		//HSYNC
		GpioPin<Port_I, 9>::Configure(GpioLtdc14);		//VSYNC
		LcdDisp.Init(GpioOutput, true);
		LcdBlacklightCtrl.Init(GpioOutput, true);

		//Print clocks
		RccClocks clocks = {};
		rcc.GetSystemClocksFreq(clocks);
		this->Printf("-SysClkFreq: %d\r\n", clocks.SysClkFreq);
		this->Printf("-HClkFreq: %d\r\n", clocks.HClkFreq);
		this->Printf("-PClk1Freq: %d\r\n", clocks.PClk1Freq);
		this->Printf("-PClk2Freq: %d\r\n", clocks.PClk2Freq);
		this->Printf("-LCD_CLK: %d\r\n", rcc.GetLcdFreq());
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
