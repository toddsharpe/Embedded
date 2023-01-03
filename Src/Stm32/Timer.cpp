#include "Stm32/Timer.h"
#include <stm32f7xx.h>

namespace Stm32
{
	Timer::Timer(TIM_TypeDef *timer) :
		m_timer(timer)
	{
	}

	void Timer::Init(const uint32_t clkFreq, const uint32_t ms)
	{
		SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
		NVIC_SetPriority(TIM2_IRQn, 0x03);
		NVIC_EnableIRQ(TIM2_IRQn);

		m_timer->CR1 &= ~(TIM_CR1_CEN);
		if (m_timer == TIM2)
		{
			RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST);
			RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST);
		}

		m_timer->PSC = clkFreq / 1000;
		m_timer->ARR = ms - 1;
		m_timer->CNT = 0;
		m_timer->EGR |= TIM_EGR_UG;
		m_timer->DIER |= TIM_DIER_UIE;
		m_timer->CR1 |= TIM_CR1_CEN;
	}
}
