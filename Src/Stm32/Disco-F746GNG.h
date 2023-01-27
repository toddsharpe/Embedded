#pragma once

#include "Board.h"

#include "Stm32/Ltdc.h"
#include "Stm32/Rcc.h"
#include "Stm32/Usart.h"
#include "Stm32/GpioPin.h"
#include "Stm32/Pll.h"
#include "Stm32/SystemClock.h"

#include <cstdint>
#include <cstdarg>
#include <string>

namespace Stm32
{
	class DiscoF746GNG : public Board
	{
	public:
		DiscoF746GNG();

		void Init();

		virtual void Printf(const char *format, ...) override;
		virtual void Printf(const char *format, va_list args) override;
		virtual void Write(const std::string &str) override;
		virtual uint32_t GetSysClkFreq() const override;

		//Peripherals
		Rcc rcc;
		Usart uart;
		Ltdc ltdc;
		GpioPin<Port_I, 12> LcdDisp;
		GpioPin<Port_K, 3> LcdBlacklightCtrl;

	private:
		static constexpr PllConfig const PllConfig200MHz =
		{
			.Source = PllSrc::HSE,
			.M = 25,
			.N = 400,
			.P = PllDiv::Div2,
			.Q = 9
		
		};

		//Creates 9.6MHz pixel clock
		static constexpr PllSaiConfig const PllSaiConfig200MHz =
		{
			.N = 384,
			.P = PllDiv::Div8,
			.Q = 2,
			.QDiv = 1,
			.R = 5,
			.RDiv = DivR8
		};

		//200MHz SYS, 50MHz APB1, 100MHz APB2
		static constexpr SystemClockConfig const SysClock200MHz =
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
			.DisplayWidth = 480,
			.DisplayHeight = 272,
			.Hsync = 41,
			.Hbp = 13,
			.Hfp = 32,
			.Vsync = 10,
			.Vbp = 2,
			.Vfp = 2
		};

	public:
		static constexpr size_t ScreenWidth()
		{
			return RK043FN48HConfig.DisplayWidth;
		}

		static constexpr size_t ScreenHeight()
		{
			return RK043FN48HConfig.DisplayHeight;
		}
	};
}
