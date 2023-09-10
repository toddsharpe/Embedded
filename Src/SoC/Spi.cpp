#include "SoC/Spi.h"

namespace SoC
{
	Spi::Spi(spi_block *spi) :
		OutputChannel(),
		m_spi(spi)
	{
	}

	// Write in 8bit chunks
	void Spi::Write(const ReadOnlyBuffer& buffer)
	{
		const uint8_t *data = (uint8_t*)buffer.Data;
		for (size_t i = 0; i < buffer.Length; i++)
		{
			while (SPI1->txdata.full) {};
			SPI1->txdata.data = data[i];
		}
		while (SPI1->txdata.full) {};
	}
}
