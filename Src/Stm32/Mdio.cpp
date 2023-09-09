#include "Stm32/Mdio.h"
#include "Assert.h"
#include "Util.h"
#include <stm32f7xx.h>

namespace Stm32
{
	Mdio::Mdio(ETH_TypeDef* eth):
		Sys::Mdio(),
		m_eth(eth)
	{

	}

	uint16_t Mdio::ReadRegister(const uint32_t PhyAddr, const uint32_t RegAddr)
	{
		//Set MII address register
		MODIFY_REG(m_eth->MACMIIAR, ETH_MACMIIAR_MB, 0);
		MODIFY_REG(m_eth->MACMIIAR, ETH_MACMIIAR_MW, 0);
		MODIFY_REG(m_eth->MACMIIAR, ETH_MACMIIAR_MR, RegAddr << ETH_MACMIIAR_MR_Pos);
		MODIFY_REG(m_eth->MACMIIAR, ETH_MACMIIAR_PA, PhyAddr << ETH_MACMIIAR_PA_Pos);

		//Set busy bit and busy wait
		SET_BIT(m_eth->MACMIIAR, ETH_MACMIIAR_MB);
		while (READ_BIT(m_eth->MACMIIAR, ETH_MACMIIAR_MB));

		//Get value
		return (uint16_t)GET_REG_FIELD(m_eth->MACMIIDR, ETH_MACMIIDR_MD_Pos, ETH_MACMIIDR_MD_Msk);
	}

	void Mdio::WriteRegister(const uint32_t PhyAddr, const uint32_t RegAddr, const uint16_t data)
	{
		//Set MII address register
		MODIFY_REG(m_eth->MACMIIAR, ETH_MACMIIAR_MB, 0);
		MODIFY_REG(m_eth->MACMIIAR, ETH_MACMIIAR_MW, 0);
		MODIFY_REG(m_eth->MACMIIAR, ETH_MACMIIAR_MR, RegAddr << ETH_MACMIIAR_MR_Pos);
		MODIFY_REG(m_eth->MACMIIAR, ETH_MACMIIAR_PA, PhyAddr << ETH_MACMIIAR_PA_Pos);

		//Set value
		m_eth->MACMIIDR = data;

		//Mark as write, set busy bit and busy wait
		SET_BIT(m_eth->MACMIIAR, ETH_MACMIIAR_MW);
		SET_BIT(m_eth->MACMIIAR, ETH_MACMIIAR_MB);
		while (READ_BIT(m_eth->MACMIIAR, ETH_MACMIIAR_MB));
	}
}
