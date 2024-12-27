#pragma once

#if defined(STM32F746xx)
	#include <stm32f746xx.h>
#else
	#include "stm32f401xc.h"
#endif
#include "Util.h"
#include "Assert.h"

namespace Stm32
{
	struct PwmConfig
	{
		uint32_t Period;
		bool Ch1Enabled;
		bool Ch2Enabled;
		bool Ch3Enabled;
		bool Ch4Enabled;
	};

	struct PwmValues
	{
		uint32_t Ch1Value;
		uint32_t Ch2Value;
		uint32_t Ch3Value;
		uint32_t Ch4Value;
	};
	
	//Assumes active high outputs
	class Pwm
	{
	public:
		Pwm(TIM_TypeDef *timer):
			m_timer(timer)
		{

		}

		void Init(const uint32_t clkFreq, const PwmConfig& config)
		{
			Assert(clkFreq % Mhz == 0);

			m_timer->CR1 &= ~(TIM_CR1_CEN);
			CLEAR_BIT(m_timer->CR1, TIM_CR1_DIR); //Upwards
			m_timer->PSC = clkFreq / 1'000'000;
			m_timer->ARR = config.Period - 1;

			//Configure channels
			//-PWM mode
			//-Output compare preload enabled
			//-Enable
			if (config.Ch1Enabled)
			{
				MODIFY_REG(m_timer->CCMR1, TIM_CCMR1_OC1M, 0b110 << TIM_CCMR1_OC1M_Pos);
				MODIFY_REG(m_timer->CCMR1, TIM_CCMR1_OC1PE, TIM_CCMR1_OC1PE);
				MODIFY_REG(m_timer->CCER, TIM_CCER_CC1E, TIM_CCER_CC1E);
			}
			if (config.Ch2Enabled)
			{
				MODIFY_REG(m_timer->CCMR1, TIM_CCMR1_OC2M, 0b110 << TIM_CCMR1_OC2M_Pos);
				MODIFY_REG(m_timer->CCMR1, TIM_CCMR1_OC2PE, TIM_CCMR1_OC2PE);
				MODIFY_REG(m_timer->CCER, TIM_CCER_CC2E, TIM_CCER_CC2E);
			}
			if (config.Ch3Enabled)
			{
				MODIFY_REG(m_timer->CCMR2, TIM_CCMR2_OC3M, 0b110 << TIM_CCMR2_OC3M_Pos);
				MODIFY_REG(m_timer->CCMR2, TIM_CCMR2_OC3PE, TIM_CCMR2_OC3PE);
				MODIFY_REG(m_timer->CCER, TIM_CCER_CC3E, TIM_CCER_CC3E);
			}
			if (config.Ch4Enabled)
			{
				MODIFY_REG(m_timer->CCMR2, TIM_CCMR2_OC4M, 0b110 << TIM_CCMR2_OC4M_Pos);
				MODIFY_REG(m_timer->CCMR2, TIM_CCMR2_OC4PE, TIM_CCMR2_OC4PE);
				MODIFY_REG(m_timer->CCER, TIM_CCER_CC4E, TIM_CCER_CC4E);
			}

			//Enable
			m_timer->EGR |= TIM_EGR_UG;
			m_timer->CR1 |= TIM_CR1_CEN;
		}

		void Set(PwmValues values)
		{
			m_timer->CCR1 = values.Ch1Value;
			m_timer->CCR2 = values.Ch2Value;
			m_timer->CCR3 = values.Ch3Value;
			m_timer->CCR4 = values.Ch4Value;
		}

	private:
		static constexpr uint32_t Mhz = 1'000'000;

		TIM_TypeDef *const m_timer;
	};
}
