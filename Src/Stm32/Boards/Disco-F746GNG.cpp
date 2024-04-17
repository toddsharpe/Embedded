#include "Stm32/Boards/Disco-F746GNG.h"
#include "Stm32/Pll.h"
#include "Stm32/SysCfg.h"
#include "Stm32/SystemClock.h"
#include "Stm32/Rcc.h"
#include "Stm32/GpioPin.h"

#include <stm32f746xx.h>

using namespace Stm32;

namespace Board
{
	static constexpr PllConfig const PllConfig216MHz =
	{
		.Source = PllSrc::HSE,
		.M = 25,
		.N = 432,
		.P = PllDiv::Div2,
		.Q = 9
	
	};

	//Creates 9.6MHz LCD_TFT clock
	static constexpr PllSaiConfig const PllSaiConfig216MHz =
	{
		.N = 384,
		.P = PllDiv::Div8,
		.Q = 2,
		.QDiv = 1,
		.R = 5,
		.RDiv = DivR8
	};

	//216MHz SYS, 54MHz APB1, 108MHz APB2
	static constexpr SystemClockConfig const SysClock216MHz =
	{
		.Source = RCC_CFGR_SW_PLL,
		.AHBCLKDivider = RCC_CFGR_HPRE_DIV1,
		.APB1CLKDivider = RCC_CFGR_PPRE1_DIV4,
		.APB2CLKDivider = RCC_CFGR_PPRE2_DIV2,
		.FlashLatency = FLASH_ACR_LATENCY_5WS
	};

	//LCD Configuration
	static constexpr LtdcConfig const RK043FN48HConfig
	{
		.DisplayWidth = DisplayWidth,
		.DisplayHeight = DisplayHeight,
		.Hsync = 41,
		.Hbp = 13,
		.Hfp = 32,
		.Vsync = 10,
		.Vbp = 2,
		.Vfp = 2
	};

	//Peripherals
	Rcc rcc(16'000'000, 25'000'000);
	Usart uart(USART1);
	Ltdc ltdc(RK043FN48HConfig);
	GpioPin LcdDisp(GPIOI, 12);
	GpioPin LcdBlacklightCtrl(GPIOK, 3);

	void Init()
	{
		//Initialize peripherals
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN);
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACRXEN);
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACTXEN);
		__DSB();

		//Enable RMII
		SysCfg::Init();
		
		//Initialize system clock
		Pll::Init(PllConfig216MHz);
		SystemClock::Init(SysClock216MHz);
		Pll::Init(PllSaiConfig216MHz);

		//Initialize Uart
		GpioPin::Configure(GPIOA, 9, GpioUart1);
		GpioPin::Configure(GPIOB, 7, GpioUart1);
		uart.Init(rcc.GetPClk2Freq(), UartDefault);
		Board::Printf("Board: Disco-F746GNG\r\n");

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
		GpioPin::Configure(GPIOG, 14, GpioEth);	//MII_TXD1

		//Initialize LTDC
		GpioPin::Configure(GPIOI, 15, GpioLtdc14); //R0
		GpioPin::Configure(GPIOJ, 0, GpioLtdc14); //R1
		GpioPin::Configure(GPIOJ, 1, GpioLtdc14); //R2
		GpioPin::Configure(GPIOJ, 2, GpioLtdc14); //R3
		GpioPin::Configure(GPIOJ, 3, GpioLtdc14); //R4
		GpioPin::Configure(GPIOJ, 4, GpioLtdc14); //R5
		GpioPin::Configure(GPIOJ, 5, GpioLtdc14); //R6
		GpioPin::Configure(GPIOJ, 6, GpioLtdc14); //R7
		GpioPin::Configure(GPIOJ, 7, GpioLtdc14); //G0
		GpioPin::Configure(GPIOJ, 8, GpioLtdc14); //G1
		GpioPin::Configure(GPIOJ, 9, GpioLtdc14); //G2
		GpioPin::Configure(GPIOJ, 10, GpioLtdc14); //G3
		GpioPin::Configure(GPIOJ, 11, GpioLtdc14); //G4
		GpioPin::Configure(GPIOK, 0, GpioLtdc14); //G5
		GpioPin::Configure(GPIOK, 1, GpioLtdc14); //G6
		GpioPin::Configure(GPIOK, 2, GpioLtdc14); //G7
		GpioPin::Configure(GPIOE, 4, GpioLtdc14); //B0
		GpioPin::Configure(GPIOJ, 13, GpioLtdc14); //B1
		GpioPin::Configure(GPIOJ, 14, GpioLtdc14); //B2
		GpioPin::Configure(GPIOJ, 15, GpioLtdc14); //B3
		GpioPin::Configure(GPIOG, 12, GpioLtdc9); //B4
		GpioPin::Configure(GPIOK, 4, GpioLtdc14); //B5
		GpioPin::Configure(GPIOK, 5, GpioLtdc14); //B6
		GpioPin::Configure(GPIOK, 6, GpioLtdc14); //B7
		GpioPin::Configure(GPIOK, 7, GpioLtdc14); //DE
		GpioPin::Configure(GPIOI, 14, GpioLtdc14); //CLK
		GpioPin::Configure(GPIOI, 10, GpioLtdc14); //HSYNC
		GpioPin::Configure(GPIOI, 9, GpioLtdc14); //VSYNC
		LcdDisp.Init(GpioOutput, true);
		LcdBlacklightCtrl.Init(GpioOutput, true);

		//Print welcome
		Board::Printf("    Initialized\r\n");

		//Print clocks
		RccClocks clocks = {};
		rcc.GetSystemClocksFreq(clocks);
		Board::Printf("-SysClkFreq: %d\r\n", clocks.SysClkFreq);
		Board::Printf("-HClkFreq: %d\r\n", clocks.HClkFreq);
		Board::Printf("-PClk1Freq: %d\r\n", clocks.PClk1Freq);
		Board::Printf("-PClk2Freq: %d\r\n", clocks.PClk2Freq);
		Board::Printf("-LCD_CLK: %d\r\n", rcc.GetLcdFreq());
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
