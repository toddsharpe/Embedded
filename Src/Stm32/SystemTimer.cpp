#include "Sys/SystemTimer.h"
#if defined(STM32F746xx)
	#include <stm32f746xx.h>
#else
	#include "stm32f401xc.h"
#endif
#include "Board.h"
#include "Assert.h"

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

	void ThreadSleep(const uint32_t ms)
	{
		const uint32_t stop = m_ticks +  ms;
		while (m_ticks < stop)
			__WFI();
	}

	void OnTick(void* arg)
	{
		m_ticks += m_freq;
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
