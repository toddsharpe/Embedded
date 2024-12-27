#pragma once

#include <cstdint>
#if defined(STM32F746xx)
	#include <stm32f746xx.h>
#else
	#include "stm32f401xc.h"
#endif

namespace Stm32
{
	class Timer
	{
	public:
		Timer(TIM_TypeDef *timer);
		void Init(const uint32_t clkFreq, const uint32_t ms);

	private:
		TIM_TypeDef *m_timer;
	};
}
