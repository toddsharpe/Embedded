// DOC: St7789.pdf

#include "Assert.h"
#include "Drivers/St7789Base.h"
#include "Rtos/Types.h"

extern void ThreadSleep(const milli_t ms);

namespace Drivers
{
	St7789Base::St7789Base(DataChannel &channel, Sys::GpioPin &dcPin, Sys::GpioPin &resetPin) :
		m_channel(channel),
		m_dcPin(dcPin),
		m_resetPin(resetPin),
		m_xOffset(0),
		m_yOffset(0)
	{
	}

	void St7789Base::Init()
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
	}

	// NOTE(tsharpe): This method doesn't allow for offsets
	void St7789Base::SetAddressWindow(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1)
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

	void St7789Base::SendCommand(const Command command)
	{
		m_dcPin.Set(false);

		uint8_t buffer[1] = {};
		buffer[0] = (uint8_t)command;
		m_channel.Write(buffer, sizeof(buffer));
	}

	void St7789Base::SendData(const uint8_t data)
	{
		m_dcPin.Set(true);

		uint8_t buffer[1] = {};
		buffer[0] = data;
		m_channel.Write(buffer, sizeof(buffer));
	}

	void St7789Base::SendData(const uint8_t *buffer, const size_t length)
	{
		m_dcPin.Set(true);

		m_channel.Write(buffer, length);
	}
}
