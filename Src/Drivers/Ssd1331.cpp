// DOC: SSD1331_1.2.pdf

#include "Assert.h"
#include "Drivers/Ssd1331.h"

extern void ThreadSleep(const milli_t ms);

namespace Drivers
{
	Ssd1331::Ssd1331(OutputChannel &channel, Sys::GpioPin &dcPin, Sys::GpioPin &resetPin) :
		m_channel(channel),
		m_dcPin(dcPin),
		m_resetPin(resetPin),
		m_xOffset(0),
		m_yOffset(0)
	{
	}

	void Ssd1331::Init()
	{
		//Pulse reset
		//m_resetPin.Set(true);
		//ThreadSleep(50);
		//m_resetPin.Set(false);
		//ThreadSleep(50);
		//m_resetPin.Set(true);
		//ThreadSleep(50);

		SendCommand(Command::SETDISPLAYON);
	}

	void Ssd1331::SendCommand(Command command)
	{
		m_dcPin.Set(false);

		uint8_t buffer[1] = {};
		buffer[0] = (uint8_t)command;
		m_channel.Write({buffer, sizeof(buffer)});
	}

	void Ssd1331::SendData(uint8_t data)
	{
		m_dcPin.Set(true);

		uint8_t buffer[1] = {};
		buffer[0] = data;
		m_channel.Write({buffer, sizeof(buffer)});
	}

	void Ssd1331::SendData(const uint8_t *buffer, size_t length)
	{
		m_dcPin.Set(true);

		m_channel.Write({buffer, length});
	}
}
