#pragma once

#include "Callback.h"
#include "Sys/DmaStream.h"

#include <stm32f746xx.h>
#include <stm32f7xx.h>

namespace Stm32
{
	enum DmaStreamDir
	{
		PeriphToMemory = 0,
		MemoryToPeriph = DMA_SxCR_DIR_0,
		MemoryToMem = DMA_SxCR_DIR_1
	};

	enum DmaStreamDataSize
	{
		Byte = 0,
		HalfWord = 1,
		Word = 2,
	};

	struct DmaStreamConfig
	{
		uint8_t Channel;
		DmaStreamDir Direction;
		bool MemInc;
		bool PeriphInc;
		DmaStreamDataSize MemSize;
		DmaStreamDataSize PeriphSize;
	};

	static constexpr DmaStreamConfig const SPI1_TX_Stream3Channel3 =
	{
		.Channel = 3,
		.Direction = DmaStreamDir::MemoryToPeriph,
		.MemInc = true,
		.PeriphInc = false,
		.MemSize = DmaStreamDataSize::HalfWord,
		.PeriphSize = DmaStreamDataSize::HalfWord,
	};

	class DmaStream : public Sys::DmaStream
	{
	public:
		DmaStream(DMA_Stream_TypeDef* stream, DMA_TypeDef* dma);

		void Init(const DmaStreamConfig& config);
		virtual void Start(const void* source, const void* destination, const size_t length) override;

		IRQn_Type GetInterupt();

	private:
		//NOTE(tsharpe): LISR is for streams 0-3, HISR for streams 4-7
		virtual void OnInterrupt() override;

		DMA_Stream_TypeDef* m_stream;
		DMA_TypeDef* m_dma;
	};
}
