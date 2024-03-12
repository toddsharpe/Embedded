#include "Stm32/Board.h"
#include "Stm32/Pll.h"
#include "Stm32/SystemClock.h"
#include "Stm32/SysCfg.h"
#include "Stm32/Rcc.h"
#include "Stm32/Usart.h"
#include "Stm32/GpioPin.h"
#include "Stm32/Pll.h"
#include "Stm32/SystemClock.h"
#include "Stm32/EthMac.h"
#include "Net/IpStack.h"

#include <stm32f746xx.h>

// MAN: um1974-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf

using namespace Stm32;

namespace Board
{
	//Static eth buffers
	static uint8_t TxBuffers[Stm32::EthMac::BufferCount][Stm32::EthMac::BufferSize];
	static uint8_t RxBuffers[Stm32::EthMac::BufferCount][Stm32::EthMac::BufferSize];

	//IP Buffers
	static StaticBuffer<Stm32::EthMac::BufferSize> IpTxBuffer;
	static StaticBuffer<Stm32::EthMac::BufferSize> IpSysBuffer;

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
	EthMac mac(ETH, TxBuffers, RxBuffers);
	GpioPin<Port_B, 0> Led1;
	GpioPin<Port_B, 7> Led2;
	GpioPin<Port_B, 14> Led3;

	//IP stack
	Net::IpStack ip(mac);

	void Init()
	{
		SysCfg::Init();
		
		//Initialize peripherals
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);
		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN);
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);
		__DSB();
	
		//Initialize system: PLL, System Clock, SysCfg
		Pll::Init(PllConfig216MHz);
		SystemClock::Init(SysClock216MHz);

		//Initialize UART
		GpioPin<Port_D, 8>::Configure(GpioUart3);
		GpioPin<Port_D, 9>::Configure(GpioUart3);
		uart.Init(rcc.GetPClk1Freq(), UartDefault);
		Board::Printf("Board: NucleoF746ZG\r\n");

		//Initialize Ethernet
		//MAN: Table 11
		GpioPin<Port_A, 1>::Configure(GpioEth);		//MII_RX_CLK
		GpioPin<Port_A, 2>::Configure(GpioEth);		//MII_MDIO
		GpioPin<Port_C, 1>::Configure(GpioEth);		//MII_MDC
		GpioPin<Port_A, 7>::Configure(GpioEth);		//MII_RX_DV
		GpioPin<Port_C, 4>::Configure(GpioEth);		//MII_RXD0
		GpioPin<Port_C, 5>::Configure(GpioEth);		//MII_RXD1
		GpioPin<Port_G, 11>::Configure(GpioEth);	//MII_TX_EN
		GpioPin<Port_G, 13>::Configure(GpioEth);	//MII_TXD0
		GpioPin<Port_B, 13>::Configure(GpioEth);	//MII_TXD1

		//Initialize ethernet/ip layers
		mac.Init();
		ip.InitBuffers(IpTxBuffer, IpSysBuffer);
		ip.Display();

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

	uint32_t GetSysClkFreq()
	{
		return rcc.GetSysClkFreq();
	}

	void Write(const void* const buffer)
	{
		const char* str = static_cast<const char*>(buffer);
		uart.Write(str, strlen(str));
	}
}
