#pragma once

#include <cstdint>

namespace Stm32
{
	/*
	enum SystemClockSource
	{
		HSI = RCC_CFGR_SW_HSI,
		HSE = RCC_CFGR_SW_HSE,
		PLLCLK = RCC_CFGR_SW_PLL,
	};
	*/

	struct SystemClockConfig
	{
		//SystemClockSource SysClock;
		uint32_t Source;
		uint32_t AHBCLKDivider;
		uint32_t APB1CLKDivider;
		uint32_t APB2CLKDivider;

		uint32_t FlashLatency;
	};

	class SystemClock
	{
	public:
		static void Init(const SystemClockConfig& config);
	};
}
