// DOC: St7789.pdf

#pragma once

#include "Graphics/FrameBuffer.h"
#include "Rtos/Kernel.h"

namespace Drivers
{
	//Framebuffer/commands/simple data is sent with SPI polling.
	template <class TChannel, class TGpio>
	class St7789_Base
	{
	public:
		St7789_Base(TChannel& channel, TGpio& dcPin, TGpio& resetPin) :
			m_channel(channel),
			m_dcPin(dcPin),
			m_resetPin(resetPin)
		{}

		void Init()
		{
			m_resetPin.Set(true);
			Rtos::SleepThread(50);
			m_resetPin.Set(false);
			Rtos::SleepThread(50);
			m_resetPin.Set(true);
			Rtos::SleepThread(50);

			SendCommand(Command::SWRESET);
			Rtos::SleepThread(150);

			SendCommand(Command::SLPOUT);
			Rtos::SleepThread(500);

			SendCommand(Command::COLMOD);
			SendData(COLOR_MODE_16bit);
			Rtos::SleepThread(10);

			SendCommand(Command::MADCTL);
			{
				MADCTL_REG reg = {0};
				// reg.MV = 1;
				SendData(reg.AsUint8);
			}

			SendCommand(Command::INVON);
			Rtos::SleepThread(10);
			SendCommand(Command::NORON);
			Rtos::SleepThread(10);
			SendCommand(Command::DISPON);
			Rtos::SleepThread(10);
		}

		virtual void Write(Graphics::FrameBuffer& framebuffer) = 0;

	protected:
		static constexpr uint8_t COLOR_MODE_16bit = 0x55; // RGB565 (16bit)

		//DOC 9.1 System Function Command Table 1
		enum Command : uint8_t
		{
			NOP = 0x00,
			SWRESET = 0x01,
			RDDID = 0x04,
			RDDST = 0x09,

			SLPIN = 0x10,
			SLPOUT = 0x11,
			PTLON = 0x12,
			NORON = 0x13,

			INVOFF = 0x20,
			INVON = 0x21,
			DISPOFF = 0x28,
			DISPON = 0x29,
			CASET = 0x2A,
			RASET = 0x2B,
			RAMWR = 0x2C,
			MADCTL = 0x36,
			COLMOD = 0x3A,
		};

		//9.1.28 MADCTL (36h): Memory Data Access Control 
		struct MADCTL_REG
		{
			union
			{
				struct
				{
					uint8_t Reserved : 2;
					uint8_t MH : 1; // Display Data Latch Data Order. 0 = Left to right, 1 = Right to Left
					uint8_t RGB : 1; // RGB/BGR Order. 0 = RGB, 1 = BGR
					uint8_t ML : 1; // Line Address Order. 0 = Top to bottom, 1 = Bottom to Top
					uint8_t MV : 1; // Page/Column Order. 0 = Normal mode, 1 = Reverse mode
					uint8_t MX : 1; // Column Address Order. 0 = Left to Right. 1 = Right to Left.
					uint8_t MY : 1; // Page Address Order. 0 = Top to Bottom, 1 = Bottom to top.
				};
				uint8_t AsUint8;
			};
		};

		void SetAddressWindow(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1)
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

		void SendCommand(const Command command)
		{
			m_dcPin.Set(false);

			uint8_t buffer[1] = {};
			buffer[0] = (uint8_t)command;
			m_channel.Write({buffer, sizeof(buffer)});
		}

		void SendData(const uint8_t data)
		{
			m_dcPin.Set(true);

			uint8_t buffer[1] = {};
			buffer[0] = data;
			m_channel.Write({buffer, sizeof(buffer)});
		}

		void SendData(const uint8_t* buffer, const size_t length)
		{
			m_dcPin.Set(true);

			m_channel.Write({buffer, length});
		}

		TChannel& m_channel;
		TGpio& m_dcPin;
		TGpio& m_resetPin;
	};
}
