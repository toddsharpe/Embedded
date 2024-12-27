#include "Assert.h"
#include "Stm32/SystemClock.h"

#if defined(STM32F746xx)
	#include <stm32f746xx.h>
	#include <stm32f7xx.h>
#else
	#include "stm32f401xc.h"
#endif
#include "Util.h"

namespace Stm32
{
	void SystemClock::Init(const SystemClockConfig& config)
	{
		//NOTE(tsharpe): Not implemented (will affect UART baud rate calc)
		Assert(config.AHBCLKDivider == RCC_CFGR_HPRE_DIV1);
		
		//Set flash latency
		MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, config.FlashLatency);
		
		//Set clocks
		MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, config.AHBCLKDivider);
		MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, config.Source);
		MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, config.APB1CLKDivider);
		MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, config.APB2CLKDivider);
	}
}
