#include "Sys/SystemTimer.h"
#include <stm32f746xx.h>

namespace SystemTimer
{
	static TickFreq m_freq;
	static uint32_t m_ticks;

	void Init(const uint32_t sysFreq, const TickFreq tickFreq)
	{
		m_freq = tickFreq;
		const uint32_t ticks = sysFreq / (1000U / tickFreq);
		SysTick->LOAD = (uint32_t)(ticks - 1UL);
		SysTick->VAL = 0;
		SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
	}

	void Start()
	{
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	}

	void Stop()
	{
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	}

	void OnTick()
	{
		m_ticks += m_freq;
	}

	uint32_t GetTicks()
	{
		return m_ticks;
	}
}
