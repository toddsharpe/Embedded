// DOC: St7789.pdf

#pragma once

#include "Buffer.h"
#include "Rtos/KEvent.h"
#include "Graphics/FrameBuffer.h"
#include "Drivers/St7789_Base.h"

namespace Drivers
{
	//Framebuffer is sent via DMA, commands/simple data is sent with SPI polling.
	template <class TChannel, class TGpio, class TDma>
	class St7789_Dma : public St7789_Base<TChannel, TGpio>
	{
	public:
		typedef St7789_Base<TChannel, TGpio> Base;
		
		St7789_Dma(TChannel& channel, TGpio& dcPin, TGpio& resetPin, TDma& dma) :
			Base(channel, dcPin, resetPin),
			m_dma(dma),
			m_writeAddress(channel.Data())
		{}

		void Write(Graphics::FrameBuffer& framebuffer)
		{
			// Set address
			Base::SetAddressWindow(0, 0, framebuffer.GetWidth() - 1, framebuffer.GetHeight() - 1);

			const size_t cells = framebuffer.GetWidth() * framebuffer.GetHeight();
			AssertOp(cells, <, TDma::MaxTransfer);
			SendDataDMA((uint16_t *)framebuffer.GetBuffer(), cells);
		}

	private:
		void SendDataDMA(const uint16_t* buffer, size_t length)
		{
			Base::m_dcPin.Set(true);
			m_dma.Start(buffer, m_writeAddress, length);
		}

		TDma& m_dma;
		void* const m_writeAddress;
	};
}
