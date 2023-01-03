#pragma once

#include <cstdint>
#include <stm32f746xx.h>

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
	};

	static constexpr SystemClockConfig const DefaultSysClock =
	{
		.Source = RCC_CFGR_SW_PLL,
		.AHBCLKDivider = RCC_CFGR_HPRE_DIV1,
		.APB1CLKDivider = RCC_CFGR_PPRE1_DIV2,
		.APB2CLKDivider = RCC_CFGR_PPRE2_DIV1
	};

	class SystemClock
	{
	public:
		static void Init(const SystemClockConfig& config);
	};
}
