#pragma once

#include "DirectDataChannel.h"

#include <cstdint>
#include <stm32f7xx.h>
#include <stm32f746xx.h>

namespace Stm32
{
	struct SpiConfig
	{
		bool CPOL;
		bool CPHA;
		bool SoftwareSlaveManagement;
		bool SpiMaster;
		uint32_t PClkDiv;
		bool EnableDMA;
	};

	//NOTE(tsharpe): Logic analyzer only goes up to 24MHz
	static constexpr SpiConfig const SpiMode3 = {.CPOL = true, .CPHA = true, .SoftwareSlaveManagement = true, .SpiMaster = true, .PClkDiv = SPI_CR1_BR_0, .EnableDMA = true};

	class Spi : public DirectDataChannel
	{
	public:
		Spi(SPI_TypeDef *spi);

		void Init(const SpiConfig& config);

		virtual void Write(const uint8_t* buffer, size_t length) override;
		virtual void Read(uint8_t* buffer, size_t length) override;
		virtual size_t BytesAvailable() override;
		virtual void* GetWriteAddress() override;

	private:
		SPI_TypeDef *m_spi;
	};
}
