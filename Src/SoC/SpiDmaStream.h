#pragma once

#include "Callback.h"
#include "Sys/DmaStream.h"

#include <SoC.h>

namespace SoC
{
	enum DmaStreamDir
	{
		PeriphToMemory = 0,
		MemoryToPeriph = 1,
	};

	enum DmaStreamDataSize
	{
		Byte = 0,
		HalfWord = 1,
		Word = 2,
	};

	struct DmaStreamConfig
	{
		DmaStreamDir Direction;
		DmaStreamDataSize Size;
	};

	static constexpr DmaStreamConfig const Spi_HWrite =
	{
		.Direction = DmaStreamDir::MemoryToPeriph,
		.Size = DmaStreamDataSize::HalfWord,
	};

	class SpiDmaStream : public Sys::DmaStream
	{
	public:
		SpiDmaStream(spi_dma_block* stream);

		void Init(const DmaStreamConfig& config);
		virtual void Start(const void* source, const void* destination, const size_t length) override;

	private:
		virtual void OnInterrupt() override;

		spi_dma_block* const m_stream;
	};
}
