#include "SoC/SpiDmaStream.h"

#include "Assert.h"

namespace SoC
{

	SpiDmaStream::SpiDmaStream(spi_dma_block* stream) :
		Sys::DmaStream(),
		m_stream(stream)
	{

	}

	void SpiDmaStream::Init(const DmaStreamConfig& config)
	{
		Assert(config.Direction == DmaStreamDir::MemoryToPeriph);

		m_stream->config.start = 0;
		while (m_stream->config.busy)
			;

		m_stream->config.dir = config.Direction;
		m_stream->config.size = config.Size;
	}

	void SpiDmaStream::Start(const void* source, const void* destination, const size_t length)
	{
		Assert(m_stream->config.busy == 0);
		
		m_stream->mem_addr = (uint32_t)source;
		m_stream->periph_addr = (uint32_t)destination;
		m_stream->count = length;

		m_stream->config.start = 1;
	}

	void SpiDmaStream::OnInterrupt()
	{
		//NOTE(tsharpe): Interrupts not supported yet.
	}
}
