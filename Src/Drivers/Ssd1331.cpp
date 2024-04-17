// DOC: SSD1331_1.2.pdf

#include "Assert.h"
#include "Drivers/Ssd1331.h"

extern void ThreadSleep(const milli_t ms);

namespace Drivers
{
	Ssd1331::Ssd1331(DataChannel &channel, Sys::GpioPin &dcPin, Sys::GpioPin &resetPin) : m_channel(channel),
																														 m_dcPin(dcPin),
																														 m_resetPin(resetPin),
																														 m_xOffset(0),
																														 m_yOffset(0)
	{
	}

	void Ssd1331::Init()
	{
		//Pulse reset
		m_resetPin.Set(true);
		ThreadSleep(50);
		m_resetPin.Set(false);
		ThreadSleep(50);
		m_resetPin.Set(true);
		ThreadSleep(50);

		//SendCommand(Command::SETDISPLAYOFF);
		//ThreadSleep(10);
		SendCommand(Command::SETREMAP);
		SendData(COLOR_MODE_16bit);
		ThreadSleep(10);

		//SendCommand(Command::SETSTARTLINE);
		//SendData(0x00);
		//SendCommand(Command::SETDISPLAYOFFSET);
		//SendData(0x00);
		//SendCommand(Command::NORMALDISPLAY);
		//ThreadSleep(10);
		//SendCommand(Command::POWERMODE);
		//SendData(0x0B);
		//ThreadSleep(10);

		SendCommand(Command::SETDISPLAYON);
	}

	void Ssd1331::Write(Graphics::FrameBuffer &framebuffer)
	{
		// Set address
		SetAddressWindow(0, 0, framebuffer.GetWidth() - 1, framebuffer.GetHeight() - 1);

		SendData((uint8_t *)framebuffer.GetBuffer(), framebuffer.Size());
	}

	void Ssd1331::SetAddressWindow(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1)
	{
		uint16_t x_start = x0, x_end = x1;
		uint16_t y_start = y0, y_end = y1;

		uint8_t b[] = {0, 0, 0, (uint8_t)x_end};
		SendData(b, sizeof(b));

		// Column address set
		SendCommand(Command::SETCOLUMN);
		{
			uint8_t data[] = {(uint8_t)(x_start >> 8), (uint8_t)(x_start & 0xFF), (uint8_t)(x_end >> 8), (uint8_t)(x_end & 0xFF)};
			SendData(data, sizeof(data));
		}

		// Row address set
		SendCommand(Command::SETROW);
		{
			uint8_t data[] = {(uint8_t)(y_start >> 8), (uint8_t)(y_start & 0xFF), (uint8_t)(y_end >> 8), (uint8_t)(y_end & 0xFF)};
			SendData(data, sizeof(data));
		}
	}

	void Ssd1331::SendCommand(Command command)
	{
		m_dcPin.Set(false);

		uint8_t buffer[1] = {};
		buffer[0] = (uint8_t)command;
		m_channel.Write(buffer, sizeof(buffer));
	}

	void Ssd1331::SendData(uint8_t data)
	{
		m_dcPin.Set(true);

		uint8_t buffer[1] = {};
		buffer[0] = data;
		m_channel.Write(buffer, sizeof(buffer));
	}

	void Ssd1331::SendData(const uint8_t *buffer, size_t length)
	{
		m_dcPin.Set(true);

		m_channel.Write(buffer, length);
	}
}
