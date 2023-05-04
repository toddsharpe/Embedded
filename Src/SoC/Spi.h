#pragma once

#include "DataChannel.h"

#include <cstdint>
#include <SoC.h>

namespace SoC
{
	class Spi : public DataChannel
	{
	public:
		Spi(spi_block *spi);

		void Init();

		virtual void Write(const uint8_t* buffer, size_t length) override;
		virtual void Read(uint8_t* buffer, size_t length) override;
		virtual size_t BytesAvailable() override;

	private:
		spi_block * const m_spi;
	};
}
