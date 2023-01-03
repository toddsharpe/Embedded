#include "Stm32/SystemTimer.h"
#include <stm32f746xx.h>

namespace Stm32
{
	SystemTimer::SystemTimer(const Sys::TickFreq freq) :
		Sys::SystemTimer(freq)
	{
		
	}

	void SystemTimer::Init(const uint32_t sysFreq)
	{
		const uint32_t ticks = sysFreq / (1000U / m_freq);
		SysTick->LOAD = (uint32_t)(ticks - 1UL);
		SysTick->VAL = 0;
		SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
	}

	void SystemTimer::Start()
	{
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	}

	void SystemTimer::Stop()
	{
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	}
}
