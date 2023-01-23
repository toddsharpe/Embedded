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
		MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, config.M << RCC_PLLCFGR_PLLM_Pos);
		MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN, config.N << RCC_PLLCFGR_PLLN_Pos);
		MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLP, config.P << RCC_PLLCFGR_PLLP_Pos);
		MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ, config.Q << RCC_PLLCFGR_PLLQ_Pos);
		MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC, config.Source << RCC_PLLCFGR_PLLSRC_Pos);

		SET_BIT(RCC->CR, RCC_CR_PLLON);

		// Wait for PLL to be ready
		while (!READ_BIT(RCC->CR, RCC_CR_PLLRDY))
			continue;
	}

	void Pll::Init(const PllSaiConfig& config)
	{
		// Disable PLL SAI
		CLEAR_BIT(RCC->CR, RCC_CR_PLLSAION);

		// Set PLL SAI Config
		MODIFY_REG(RCC->PLLSAICFGR, RCC_PLLSAICFGR_PLLSAIN, config.N << RCC_PLLSAICFGR_PLLSAIN_Pos);
		MODIFY_REG(RCC->PLLSAICFGR, RCC_PLLSAICFGR_PLLSAIP, config.P << RCC_PLLSAICFGR_PLLSAIP_Pos);
		MODIFY_REG(RCC->PLLSAICFGR, RCC_PLLSAICFGR_PLLSAIQ, config.Q << RCC_PLLSAICFGR_PLLSAIQ_Pos);
		MODIFY_REG(RCC->PLLSAICFGR, RCC_PLLSAICFGR_PLLSAIR, config.R << RCC_PLLSAICFGR_PLLSAIR_Pos);

		//DIVR division factor for LCD_CLK
		MODIFY_REG(RCC->DCKCFGR1, RCC_DCKCFGR1_PLLSAIDIVR, config.RDiv << RCC_DCKCFGR1_PLLSAIDIVR_Pos);

		// Enable PLL SAI
		SET_BIT(RCC->CR, RCC_CR_PLLSAION);

		// Wait for PLL SAI to be ready
		while (!READ_BIT(RCC->CR, RCC_CR_PLLSAIRDY))
			continue;
	}
}
