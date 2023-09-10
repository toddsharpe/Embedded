#include "Stm32/Nucleo-F746ZG.h"
#include "Stm32/Pll.h"
#include "Stm32/SystemClock.h"
#include "Stm32/SysCfg.h"

#include <stm32f746xx.h>

// MAN: um1974-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf

//Static eth buffers
static uint8_t TxBuffers[Stm32::EthMac::BufferCount][Stm32::EthMac::BufferSize];
static uint8_t RxBuffers[Stm32::EthMac::BufferCount][Stm32::EthMac::BufferSize];

//IP Buffers
static StaticBuffer<Stm32::EthMac::BufferSize> IpTxBuffer;
static StaticBuffer<Stm32::EthMac::BufferSize> IpSysBuffer;

namespace Stm32
{
	NucleoF746ZG::NucleoF746ZG() :
		Board(),
		rcc(16'000'000, 8'000'000),
		uart(USART3),
		mac(ETH, TxBuffers, RxBuffers),
		ip(mac)
	{

	}

	void NucleoF746ZG::Init()
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
		this->Printf("Board: NucleoF746ZG\r\n");

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
		this->Printf("    Initialized\r\n");

		//Print clocks
		RccClocks clocks = {};
		rcc.GetSystemClocksFreq(clocks);
		this->Printf("-SysClkFreq: %d\r\n", clocks.SysClkFreq);
		this->Printf("-HClkFreq: %d\r\n", clocks.HClkFreq);
		this->Printf("-PClk1Freq: %d\r\n", clocks.PClk1Freq);
		this->Printf("-PClk2Freq: %d\r\n", clocks.PClk2Freq);
	}

	void NucleoF746ZG::Write(const std::string& str)
	{
		uart.Write(str);
	}

	uint32_t NucleoF746ZG::GetSysClkFreq() const
	{
		return rcc.GetSysClkFreq();
	}
}
