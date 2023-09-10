#include "Stm32/Spi.h"

namespace Stm32
{
	Spi::Spi(SPI_TypeDef *spi) :
		DirectOutputChannel(),
		m_spi(spi)
	{
	}

	void Spi::Init(const SpiConfig &config)
	{
		// Set clock phase
		MODIFY_REG(m_spi->CR1, SPI_CR1_CPHA, config.CPHA ? SPI_CR1_CPHA : 0);

		// Set clock polarity
		MODIFY_REG(m_spi->CR1, SPI_CR1_CPOL, config.CPOL ? SPI_CR1_CPOL : 0);

		// Set software slave management
		if (config.SoftwareSlaveManagement)
		{
			SET_BIT(m_spi->CR1, SPI_CR1_SSM);
			SET_BIT(m_spi->CR1, SPI_CR1_SSI);
		}

		// Set as master
		if (config.SpiMaster)
			SET_BIT(m_spi->CR1, SPI_CR1_MSTR);

		// Set clock div
		MODIFY_REG(m_spi->CR1, SPI_CR1_BR, config.PClkDiv);

		// Enable DMA
		if (config.EnableDMA)
			SET_BIT(m_spi->CR2, SPI_CR2_TXDMAEN);

		// Enable
		SET_BIT(m_spi->CR1, SPI_CR1_SPE);
	}

	// Write in 8bit chunks
	void Spi::Write(const ReadOnlyBuffer& buffer)
	{
		const uint8_t *data = (uint8_t*)buffer.Data;
		for (size_t i = 0; i < buffer.Length; i++)
		{
			while (!(m_spi->SR & (SPI_SR_TXE))) {};
			*((volatile uint8_t *)&(SPI1->DR)) = data[i];
		}
		while ((m_spi->SR & (SPI_SR_BSY))) {};
	}

	void* Spi::GetWriteAddress()
	{
		return (void *)&m_spi->DR;
	}
}
