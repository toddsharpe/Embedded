#include "Board.h"
#include "Stm32/Pll.h"
#include "Stm32/SystemClock.h"
#include "Stm32/SysCfg.h"
#include "Stm32/Rcc.h"
#include "Stm32/Usart.h"
#include "Stm32/GpioPin.h"
#include "Stm32/Pll.h"
#include "Sys/EthMac.h"
#include "Net/IpStack.h"

#include <stm32f746xx.h>

// MAN: um1974-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf

using namespace Stm32;
using namespace Net;

//SB121, SB122 -> OFF,ON (D11 gets connected to STM32 PB5)
namespace Board
{
	//Peripheral configuration
	static constexpr PllConfig const PllConfig72MHz =
	{
		.Source = PllSrc::HSE,
		.M = 4,
		.N = 72,
		.P = PllDiv::Div2,
		.Q = 3
	};

	//72MHz SYS, 36MHz APB1, 72MHz APB2
	static constexpr SystemClockConfig const SysClock72MHz =
	{
		.Source = RCC_CFGR_SW_PLL,
		.AHBCLKDivider = RCC_CFGR_HPRE_DIV1,
		.APB1CLKDivider = RCC_CFGR_PPRE1_DIV2,
		.APB2CLKDivider = RCC_CFGR_PPRE2_DIV1,
		.FlashLatency = FLASH_ACR_LATENCY_2WS
	};

	static constexpr PllConfig const PllConfig216MHz =
	{
		.Source = PllSrc::HSE,
		.M = 4,
		.N = 216,
		.P = PllDiv::Div2,
		.Q = 9
	};

	//216MHz SYS, 54Hz APB1, 108MHz APB2
	static constexpr SystemClockConfig const SysClock216MHz =
	{
		.Source = RCC_CFGR_SW_PLL,
		.AHBCLKDivider = RCC_CFGR_HPRE_DIV1,
		.APB1CLKDivider = RCC_CFGR_PPRE1_DIV4,
		.APB2CLKDivider = RCC_CFGR_PPRE2_DIV2,
		.FlashLatency = FLASH_ACR_LATENCY_5WS
	};

	//Peripherals
	Rcc rcc(16'000'000, 8'000'000);
	Usart uart(USART3);
	GpioPin Led1(GPIOB, 0);
	GpioPin Led2(GPIOB, 7);
	GpioPin Led3(GPIOB, 14);

	void Init()
	{
		//Initialize peripherals
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);
		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN);
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);
		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACRXEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACTXEN);
		SET_BIT(RCC->AHB1ENR, RCC_APB1ENR_I2C1EN);
		__DSB();
	
		//Enable RMII
		SysCfg::Init();

		//Initialize system: PLL, System Clock, SysCfg
		Pll::Init(PllConfig216MHz);
		SystemClock::Init(SysClock216MHz);

		//Initialize UART
		GpioPin::Configure(GPIOD, 8, GpioUart3);
		GpioPin::Configure(GPIOD, 9, GpioUart3);
		uart.Init(rcc.GetPClk1Freq(), UartDefault);
		Board::Printf("Board: Nucleo-F746ZG\r\n");

		//Initialize Ethernet
		//MAN: Table 11
		GpioPin::Configure(GPIOA, 1, GpioEth);	//MII_RX_CLK
		GpioPin::Configure(GPIOA, 2, GpioEth);	//MII_MDIO
		GpioPin::Configure(GPIOC, 1, GpioEth);	//MII_MDC
		GpioPin::Configure(GPIOA, 7, GpioEth);	//MII_RX_DV
		GpioPin::Configure(GPIOC, 4, GpioEth);	//MII_RXD0
		GpioPin::Configure(GPIOC, 5, GpioEth);	//MII_RXD1
		GpioPin::Configure(GPIOG, 11, GpioEth);	//MII_TX_EN
		GpioPin::Configure(GPIOG, 13, GpioEth);	//MII_TXD0
		GpioPin::Configure(GPIOB, 13, GpioEth);	//MII_TXD1

		//Initialize I2C1
		GpioPin::Configure(GPIOB, 8, GpioI2c1);
		GpioPin::Configure(GPIOB, 9, GpioI2c1);

		//Initialize SPI1
		GpioPin::Configure(GPIOA, 5, GpioSpi1);
		GpioPin::Configure(GPIOB, 5, GpioSpi1);

		//Initialize LEDs
		Led1.Init(GpioOutput);
		Led2.Init(GpioOutput);
		Led3.Init(GpioOutput);

		//Print welcome
		Board::Printf("    Initialized\r\n");

		//Print clocks
		RccClocks clocks = {};
		rcc.GetSystemClocksFreq(clocks);
		Board::Printf("-SysClkFreq: %d\r\n", clocks.SysClkFreq);
		Board::Printf("-HClkFreq: %d\r\n", clocks.HClkFreq);
		Board::Printf("-PClk1Freq: %d\r\n", clocks.PClk1Freq);
		Board::Printf("-PClk2Freq: %d\r\n", clocks.PClk2Freq);
	}

	void Write(const ReadOnlyBuffer& buffer)
	{
		uart.Write(buffer);
	}

	uint32_t GetSysClkFreq()
	{
		return rcc.GetSysClkFreq();
	}
}
