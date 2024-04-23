#pragma once

#include "Buffer.h"
#include <cstdint>
#include <stm32f7xx.h>
#include <stm32f746xx.h>

namespace Stm32
{
	struct I2cConfig
	{
		bool Master;
		bool Addr7;
		uint32_t Timing;
	};
	
	class I2c
	{
	public:
		I2c(I2C_TypeDef* const i2c);

		void Init(const I2cConfig config);
		bool Write(const uint8_t address, const ReadOnlyBuffer& buffer);

		void Probe();

	private:
		I2C_TypeDef* m_i2c;
	};
}
