#include "Stm32/Pll.h"

namespace Stm32
{
	void Pll::Init(const PllConfig &config)
	{
		// Only for HSE
		AssertEqual(config.Source, PllSrc::HSE);

		// On Nucleo, HSE clock is provided by STLink
		SET_BIT(RCC->CR, RCC_CR_HSEBYP);
		SET_BIT(RCC->CR, RCC_CR_HSEON);

		// Wait for HSE to be ready
		while (!READ_BIT(RCC->CR, RCC_CR_HSERDY))
			continue;

		// Disable PLL
		CLEAR_BIT(RCC->CR, RCC_CR_PLLON);

		// Set PLL Config
		RCC_PLLCFGR cfgr;
		cfgr.AsUint32 = RCC->PLLCFGR;
		cfgr.PLLM = config.M;
		cfgr.PLLN = config.N;
		cfgr.PLLP = config.P;
		cfgr.PLLSRC = config.Source;
		cfgr.PLLQ = config.Q;
		RCC->PLLCFGR = cfgr.AsUint32;

		// Enable PLL
		SET_BIT(RCC->CR, RCC_CR_PLLON);

		// Wait for PLL to be ready
		while (!READ_BIT(RCC->CR, RCC_CR_PLLRDY))
			continue;
	}
}
