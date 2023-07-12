#include "SoC/Spi.h"

namespace SoC
{
	Spi::Spi(spi_block *spi) :
		DirectDataChannel(),
		m_spi(spi)
	{
	}

	void Spi::Init()
	{

	}

	// Write in 8bit chunks
	void Spi::Write(const uint8_t *buffer, size_t length)
	{
		for (size_t i = 0; i < length; i++)
		{
			while (UART->txdata.full) {};
			SPI1->txdata.data = buffer[i];
		}
		while (SPI1->txdata.full) {};
	}

	void Spi::Read(uint8_t *buffer, size_t length)
	{
		// TODO(tsharpe): Not implemented
	}

	size_t Spi::BytesAvailable()
	{
		// TODO(tsharpe): Not implemented
		return 0;
	}

	void* Spi::GetWriteAddress()
	{
		return (void*)&m_spi->txdata;
	}
}
