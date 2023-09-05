#pragma once

#include <cstdint>

namespace Sys
{
	class Mdio
	{
	public:
		virtual uint16_t ReadRegister(const uint32_t PhyAddr, const uint32_t RegAddr) = 0;
		virtual void WriteRegister(const uint32_t PhyAddr, const uint32_t RegAddr, const uint16_t data) = 0;
	};
}
