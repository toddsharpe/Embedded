#include "Stm32/DmaStream.h"

#include "Assert.h"

namespace Stm32
{
	DmaStream::DmaStream(DMA_Stream_TypeDef *stream, DMA_TypeDef *dma) :
		TransferError(),
		TransferComplete(),
		m_stream(stream),
		m_dma(dma)
	{
		Assert(m_dma == DMA2);
		Assert(m_stream == DMA2_Stream3);
	}

	void DmaStream::Init(const DmaStreamConfig &config)
	{
		Assert(config.Direction == DmaStreamDir::MemoryToPeriph);

		// Stop any in progress transactions
		CLEAR_BIT(m_stream->CR, DMA_SxCR_EN);
		while (READ_BIT(m_stream->CR, DMA_SxCR_EN))
			;

		// Set config
		MODIFY_REG(m_stream->CR, DMA_SxCR_CHSEL, config.Channel << DMA_SxCR_CHSEL_Pos);
		MODIFY_REG(m_stream->CR, DMA_SxCR_DIR, config.Direction);
		MODIFY_REG(m_stream->CR, DMA_SxCR_PINC, config.PeriphInc ? DMA_SxCR_PINC : 0);
		MODIFY_REG(m_stream->CR, DMA_SxCR_MINC, config.MemInc ? DMA_SxCR_MINC : 0);
		MODIFY_REG(m_stream->CR, DMA_SxCR_MSIZE, config.MemSize << DMA_SxCR_MSIZE_Pos);
		MODIFY_REG(m_stream->CR, DMA_SxCR_PSIZE, config.PeriphSize << DMA_SxCR_PSIZE_Pos);

		// Enable direct mode
		MODIFY_REG(m_stream->FCR, DMA_SxFCR_DMDIS, 0);

		// Enable interrupts
		SET_BIT(m_stream->CR, DMA_SxCR_TCIE);  // Transfer complete
		SET_BIT(m_stream->CR, DMA_SxCR_TEIE);  // Transfer error
		SET_BIT(m_stream->CR, DMA_SxCR_DMEIE); // Direct mode error

		NVIC_EnableIRQ(GetInterupt());
	}

	void DmaStream::Start(const void *source, const void *destination, const size_t length)
	{
		AssertOp(length, <, MaxTransfer);

		m_dma->LIFCR |= DMA_LIFCR_CTCIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3 | DMA_LIFCR_CFEIF3;
		m_stream->PAR = (uint32_t)destination;
		m_stream->M0AR = (uint32_t)source;
		m_stream->NDTR = (uint16_t)length;

		// Start!
		SET_BIT(m_stream->CR, DMA_SxCR_EN);
	}

	IRQn_Type DmaStream::GetInterupt()
	{
		return IRQn_Type::DMA2_Stream3_IRQn;
	}

	// NOTE(tsharpe): LISR is for streams 0-3, HISR for streams 4-7
	void DmaStream::OnInterrupt()
	{
		bool error = false;
		if (m_dma->LISR & DMA_LISR_FEIF3)
		{
			// Can be ignored in direct mode
			m_dma->LIFCR |= DMA_LIFCR_CFEIF3;
		}

		if (m_dma->LISR & DMA_LISR_DMEIF3)
		{
			m_dma->LIFCR |= DMA_LIFCR_CDMEIF3;
			error = true;
		}

		if (m_dma->LISR & DMA_LISR_TEIF3)
		{
			m_dma->LIFCR |= DMA_LIFCR_CTEIF3;
			error = true;
		}

		if (m_dma->LISR & DMA_LISR_HTIF3)
		{
			m_dma->LIFCR |= DMA_LIFCR_CHTIF3;
			// TODO(tsharpe): Half transfer callback
		}

		if (m_dma->LISR & DMA_LISR_TCIF3)
		{
			m_dma->LIFCR |= DMA_LIFCR_CTCIF3;
			CLEAR_BIT(m_stream->CR, DMA_SxCR_EN);

			if (TransferComplete.IsCallable() && !error)
				TransferComplete.Invoke();
		}

		if (error)
		{
			if (TransferError.IsCallable())
				TransferError.Invoke();
		}

		NVIC_ClearPendingIRQ(GetInterupt());
	}
}
