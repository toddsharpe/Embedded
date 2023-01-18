#pragma once

#include "Board.h"

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

	private:
		static constexpr PllConfig const PllConfig200MHz = { .Source = PllSrc::HSE, .M = 25, .N = 400, .P = PllDiv::Div2, .Q = 9 };

		//200MHz SYS, 50MHz APB1, 100MHz APB2
		static constexpr SystemClockConfig const SysClock200MHz =
		{
			.Source = RCC_CFGR_SW_PLL,
			.AHBCLKDivider = RCC_CFGR_HPRE_DIV1,
			.APB1CLKDivider = RCC_CFGR_PPRE1_DIV4,
			.APB2CLKDivider = RCC_CFGR_PPRE2_DIV2,
			.FlashLatency = FLASH_ACR_LATENCY_5WS
		};
	};
}
