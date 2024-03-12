#pragma once

#include "Buffer.h"
#include <cstdint>
#include <SoC.h>

namespace SoC
{
	class Spi
	{
	public:
		Spi(spi_block *const spi) : 
			m_spi(spi)
		{}

		// Write in 8bit chunks
		void Write(const ReadOnlyBuffer& buffer)
		{
			const uint8_t *data = (uint8_t*)buffer.Data;
			for (size_t i = 0; i < buffer.Length; i++)
			{
				while (SPI1->txdata.full) {};
				SPI1->txdata.data = data[i];
			}
			while (SPI1->txdata.full) {};
		}

	private:
		spi_block * const m_spi;
	};
}
