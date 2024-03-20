#pragma once

#include <cstdint>

namespace Mdio
{
	uint16_t ReadRegister(const uint32_t phyAddr, const uint32_t regAddr);
	void WriteRegister(const uint32_t phyAddr, const uint32_t regAddr, const uint16_t data);
}
