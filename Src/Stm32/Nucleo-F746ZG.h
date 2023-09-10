#pragma once

#include "Board.h"

#include "Stm32/Rcc.h"
#include "Stm32/Usart.h"
#include "Stm32/GpioPin.h"
#include "Stm32/Pll.h"
#include "Stm32/SystemClock.h"
#include "Stm32/EthMac.h"
#include "Net/IpStack.h"

#include <cstdint>
#include <cstdarg>
#include <string>

namespace Stm32
{
	class NucleoF746ZG : public Board
	{
	public:
		NucleoF746ZG();

		void Init();

		virtual void Write(const std::string &str) override;
		virtual uint32_t GetSysClkFreq() const override;

		//Peripherals
		Rcc rcc;
		Usart uart;
		EthMac mac;
		GpioPin<Port_B, 0> Led1;
		GpioPin<Port_B, 7> Led2;
		GpioPin<Port_B, 14> Led3;

		//IP stack
		Net::IpStack ip;

	private:
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
	};
}
