#pragma once

#include "OutputChannel.h"

#include <cstdint>
#include <SoC.h>

namespace SoC
{
	class Spi : public OutputChannel
	{
	public:
		Spi(spi_block *spi);

		virtual void Write(const ReadOnlyBuffer& buffer) override;

	private:
		spi_block * const m_spi;
	};
}
