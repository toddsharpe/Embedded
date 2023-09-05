#pragma once

#include "Sys/Mdio.h"
#include <stm32f746xx.h>

namespace Stm32
{
	class Mdio : public Sys::Mdio
	{
	public:
		Mdio(ETH_TypeDef* eth);
		uint16_t ReadRegister(const uint32_t PhyAddr, const uint32_t RegAddr);
		void WriteRegister(const uint32_t PhyAddr, const uint32_t RegAddr, const uint16_t data);

	private:
		ETH_TypeDef* m_eth;
	};
}
