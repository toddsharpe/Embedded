#pragma once

#include "Callback.h"

#include <cstddef>
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

	//RM0385: Table 26. DMA2 request mapping.
	//Channel 3, Stream 3
	static constexpr DmaStreamConfig const SPI1_TX =
	{
		.Channel = 3,
		.Direction = DmaStreamDir::MemoryToPeriph,
		.MemInc = true,
		.PeriphInc = false,
		.MemSize = DmaStreamDataSize::HalfWord,
		.PeriphSize = DmaStreamDataSize::HalfWord,
	};

	class DmaStream
	{
	public:
		static constexpr size_t MaxTransfer = (1 << 16) - 1;
		static void OnInterrupt(void* arg) { ((DmaStream*)arg)->OnInterrupt(); };

		DmaStream(DMA_Stream_TypeDef* stream, DMA_TypeDef* dma);

		void Init(const DmaStreamConfig& config);
		void Start(const void* source, const void* destination, const size_t length);

		IRQn_Type GetInterupt();

		Callback TransferError;
		Callback TransferComplete;

	private:
		//NOTE(tsharpe): LISR is for streams 0-3, HISR for streams 4-7
		void OnInterrupt();

		DMA_Stream_TypeDef* m_stream;
		DMA_TypeDef* m_dma;
	};
}
