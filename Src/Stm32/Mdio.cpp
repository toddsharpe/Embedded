#include "Util.h"
#include <stm32f7xx.h>
#include <stm32f746xx.h>

namespace Mdio
{
	uint16_t ReadRegister(const uint32_t phyAddr, const uint32_t regAddr)
	{
		//Set MII address register
		MODIFY_REG(ETH->MACMIIAR, ETH_MACMIIAR_MB, 0);
		MODIFY_REG(ETH->MACMIIAR, ETH_MACMIIAR_MW, 0);
		MODIFY_REG(ETH->MACMIIAR, ETH_MACMIIAR_MR, regAddr << ETH_MACMIIAR_MR_Pos);
		MODIFY_REG(ETH->MACMIIAR, ETH_MACMIIAR_PA, phyAddr << ETH_MACMIIAR_PA_Pos);

		//Set busy bit and busy wait
		SET_BIT(ETH->MACMIIAR, ETH_MACMIIAR_MB);
		while (READ_BIT(ETH->MACMIIAR, ETH_MACMIIAR_MB));

		//Get value
		return (uint16_t)GET_REG_FIELD(ETH->MACMIIDR, ETH_MACMIIDR_MD_Pos, ETH_MACMIIDR_MD_Msk);
	}

	void WriteRegister(const uint32_t phyAddr, const uint32_t regAddr, const uint16_t data)
	{
		//Set MII address register
		MODIFY_REG(ETH->MACMIIAR, ETH_MACMIIAR_MB, 0);
		MODIFY_REG(ETH->MACMIIAR, ETH_MACMIIAR_MW, 0);
		MODIFY_REG(ETH->MACMIIAR, ETH_MACMIIAR_MR, regAddr << ETH_MACMIIAR_MR_Pos);
		MODIFY_REG(ETH->MACMIIAR, ETH_MACMIIAR_PA, phyAddr << ETH_MACMIIAR_PA_Pos);

		//Set value
		ETH->MACMIIDR = data;

		//Mark as write, set busy bit and busy wait
		SET_BIT(ETH->MACMIIAR, ETH_MACMIIAR_MW);
		SET_BIT(ETH->MACMIIAR, ETH_MACMIIAR_MB);
		while (READ_BIT(ETH->MACMIIAR, ETH_MACMIIAR_MB));
	}
}
