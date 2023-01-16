#pragma once

#include <cstdint>
#include <stm32f746xx.h>

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
