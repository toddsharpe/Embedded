// DOC: ST7789.pdf

#include "Assert.h"
#include "Drivers/St7789.h"

extern void ThreadSleep(const milli_t ms);

namespace Drivers
{
	void St7789::OnTransferComplete(void *arg) { ((St7789 *)arg)->OnTransferComplete(); };

	St7789::St7789(DirectDataChannel &channel, Sys::DmaStream &dmaStream, Sys::GpioPin &dcPin, Sys::GpioPin &resetPin) : m_channel(channel),
																														 m_dmaStream(dmaStream),
																														 m_dcPin(dcPin),
																														 m_resetPin(resetPin),
																														 m_xOffset(0),
																														 m_yOffset(0)
	{
	}

	void St7789::Init()
	{
		m_resetPin.Set(true);
		ThreadSleep(50);
		m_resetPin.Set(false);
		ThreadSleep(50);
		m_resetPin.Set(true);
		ThreadSleep(50);

		SendCommand(Command::SWRESET);
		ThreadSleep(150);

		SendCommand(Command::SLPOUT);
		ThreadSleep(500);

		SendCommand(Command::COLMOD);
		SendData(COLOR_MODE_16bit);
		ThreadSleep(10);

		SendCommand(Command::MADCTL);
		{
			MADCTL_REG reg = {0};
			// reg.MV = 1;
			SendData(reg.AsUint8);
		}

		SendCommand(Command::INVON);
		ThreadSleep(10);
		SendCommand(Command::NORON);
		ThreadSleep(10);
		SendCommand(Command::DISPON);
		ThreadSleep(10);

		m_dmaStream.TransferComplete.Context = this;
		m_dmaStream.TransferComplete.Handler = &St7789::OnTransferComplete;
	}

	void St7789::Write(Graphics::FrameBuffer &framebuffer)
	{
		// Set address
		SetAddressWindow(0, 0, framebuffer.GetWidth() - 1, framebuffer.GetHeight() - 1);

		const size_t cells = framebuffer.GetWidth() * framebuffer.GetHeight();
		AssertOp(cells, <, Sys::DmaStream::MaxTransfer);
		SendDataDMA((uint16_t *)framebuffer.GetBuffer(), cells);
	}

	void St7789::OnTransferComplete()
	{
		m_event.Set();
	}

	// NOTE(tsharpe): This method doesn't allow for offsets
	void St7789::SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
	{
		uint16_t x_start = x0, x_end = x1;
		uint16_t y_start = y0, y_end = y1;

		uint8_t b[] = {0, 0, 0, (uint8_t)x_end};
		SendData(b, sizeof(b));

		// Column address set
		SendCommand(Command::CASET);
		{
			uint8_t data[] = {(uint8_t)(x_start >> 8), (uint8_t)(x_start & 0xFF), (uint8_t)(x_end >> 8), (uint8_t)(x_end & 0xFF)};
			SendData(data, sizeof(data));
		}

		// Row address set
		SendCommand(Command::RASET);
		{
			uint8_t data[] = {(uint8_t)(y_start >> 8), (uint8_t)(y_start & 0xFF), (uint8_t)(y_end >> 8), (uint8_t)(y_end & 0xFF)};
			SendData(data, sizeof(data));
		}

		/* Write to RAM */
		SendCommand(Command::RAMWR);
	}

	void St7789::SendCommand(Command command)
	{
		m_dcPin.Set(false);

		uint8_t buffer[1] = {};
		buffer[0] = (uint8_t)command;
		m_channel.Write(buffer, sizeof(buffer));
	}

	void St7789::SendData(uint8_t data)
	{
		m_dcPin.Set(true);

		uint8_t buffer[1] = {};
		buffer[0] = data;
		m_channel.Write(buffer, sizeof(buffer));
	}

	void St7789::SendData(const uint8_t *buffer, size_t length)
	{
		m_dcPin.Set(true);

		m_channel.Write(buffer, length);
	}

	void St7789::SendDataDMA(const uint16_t *buffer, size_t length)
	{
		m_dcPin.Set(true);

		m_dmaStream.Start(buffer, m_channel.GetWriteAddress(), length);
		while (!m_event.IsSignalled())
			;
	}
}
