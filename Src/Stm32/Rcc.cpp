#include "Assert.h"
#include "Util.h"
#include "Stm32/Rcc.h"

#if defined(STM32F746xx)
	#include <stm32f746xx.h>
#else
	#include "stm32f401xc.h"
#endif

namespace Stm32
{
	Rcc::Rcc(const uint32_t hsiFreq, const uint32_t hseFreq) : m_hsiFreq(hsiFreq),
															   m_hseFreq(hseFreq)
	{
	}

	void Rcc::GetSystemClocksFreq(RccClocks &clocks) const
	{
		clocks.SysClkFreq = GetSysClkFreq();
		clocks.HClkFreq = clocks.SysClkFreq;
		clocks.PClk1Freq = GetPClk1Freq();
		clocks.PClk1TimerFreq = GetPClk1TimerFreq();
		clocks.PClk2Freq = GetPClk2Freq();
	}

	uint32_t Rcc::GetSysClkFreq() const
	{
		switch (RCC->CFGR & RCC_CFGR_SWS)
		{
		case RCC_CFGR_SWS_HSI:
			return m_hsiFreq;
			break;
		case RCC_CFGR_SWS_HSE:
			return m_hseFreq;
			break;
		case RCC_CFGR_SWS_PLL:
		{
			/*
			 * PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
			 * SYSCLK = PLL_VCO / PLL_P
			 */
			const uint32_t pllSource = (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
			const uint32_t pllSourceFreq = (pllSource == RCC_PLLCFGR_PLLSRC_HSI) ? m_hsiFreq : m_hseFreq;

			const uint32_t pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
			const uint32_t plln = GET_REG_FIELD(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Pos, RCC_PLLCFGR_PLLN);
			const uint32_t pllvco = (pllSourceFreq / pllm) * plln;
			const uint32_t pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos) + 1) * 2;
			return pllvco / pllp;
			break;
		}
		default:
			return m_hsiFreq;
			break;
		}
	}
#if defined(STM32F746xx)
	uint32_t Rcc::GetLcdFreq() const
	{
		Assert((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL);

		const uint32_t pllSource = (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
		const uint32_t pllSourceFreq = (pllSource == RCC_PLLCFGR_PLLSRC_HSI) ? m_hsiFreq : m_hseFreq;
		const uint32_t pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;

		const uint32_t pllsai1n = GET_REG_FIELD(RCC->PLLSAICFGR, RCC_PLLSAICFGR_PLLSAIN_Pos, RCC_PLLSAICFGR_PLLSAIN);
		const uint32_t pllsai1r = GET_REG_FIELD(RCC->PLLSAICFGR, RCC_PLLSAICFGR_PLLSAIR_Pos, RCC_PLLSAICFGR_PLLSAIR);
		const uint32_t divR = GET_REG_FIELD(RCC->DCKCFGR1, RCC_DCKCFGR1_PLLSAIDIVR_Pos, RCC_DCKCFGR1_PLLSAIDIVR);
		Assert(divR == 0b10);

		return (pllSourceFreq / pllm) * pllsai1n / pllsai1r / 8;
	}
#endif

	uint32_t Rcc::GetPClk1TimerFreq() const
	{
		const uint32_t apb1Prescaler = GET_REG_FIELD(RCC->CFGR, RCC_CFGR_PPRE1_Pos, RCC_CFGR_PPRE1);
		if (apb1Prescaler == 0)
			return GetPClk1Freq();
		else
			return GetPClk1Freq() * 2;
	}

	uint32_t Rcc::GetPClk1Freq() const
	{
		const uint32_t sysClk = GetSysClkFreq();
		return GetScaledClkFreq(sysClk, GET_REG_FIELD(RCC->CFGR, RCC_CFGR_PPRE1_Pos, RCC_CFGR_PPRE1));
	}

	uint32_t Rcc::GetPClk2Freq() const
	{
		const uint32_t sysClk = GetSysClkFreq();
		return GetScaledClkFreq(sysClk, GET_REG_FIELD(RCC->CFGR, RCC_CFGR_PPRE2_Pos, RCC_CFGR_PPRE2));
	}

	uint32_t Rcc::GetScaledClkFreq(const uint32_t sysClk, const uint32_t prescaler) const
	{
		return (sysClk >> APBPrescTable[prescaler]);
	}
}
