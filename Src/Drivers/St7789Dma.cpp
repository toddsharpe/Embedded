// DOC: St7789Dma.pdf

#include "Assert.h"
#include "Drivers/St7789Dma.h"

extern void ThreadSleep(const milli_t ms);

namespace Drivers
{
	void St7789Dma::OnTransferComplete(void *arg) { ((St7789Dma *)arg)->OnTransferComplete(); };

	St7789Dma::St7789Dma(DirectOutputChannel &channel, Sys::GpioPin &dcPin, Sys::GpioPin &resetPin, Sys::DmaStream &dmaStream) :
		St7789Base(channel, dcPin, resetPin),
		m_dmaStream(dmaStream),
		m_dmaWriteAddress(channel.GetWriteAddress()),
		m_event()
	{
	}

	void St7789Dma::Init()
	{
		St7789Base::Init();

		m_dmaStream.TransferComplete.Context = this;
		m_dmaStream.TransferComplete.Handler = &St7789Dma::OnTransferComplete;
	}

	void St7789Dma::Write(Graphics::FrameBuffer &framebuffer)
	{
		// Set address
		SetAddressWindow(0, 0, framebuffer.GetWidth() - 1, framebuffer.GetHeight() - 1);

		const size_t cells = framebuffer.GetWidth() * framebuffer.GetHeight();
		AssertOp(cells, <, Sys::DmaStream::MaxTransfer);
		SendDataDMA((uint16_t *)framebuffer.GetBuffer(), cells);
	}

	void St7789Dma::OnTransferComplete()
	{
		m_event.Set();
	}

	void St7789Dma::SendDataDMA(const uint16_t *buffer, size_t length)
	{
		m_dcPin.Set(true);

		m_dmaStream.Start(buffer, m_dmaWriteAddress, length);
		while (!m_event.IsSignalled())
			;
	}
}
