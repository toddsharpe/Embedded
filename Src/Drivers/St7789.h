// DOC: ST7789.pdf

#pragma once

#include "Rtos/Types.h"
#include "Sys/GpioPin.h"
#include "DirectDataChannel.h"
#include "Sys/DmaStream.h"
#include "Rtos/KEvent.h"
#include "Graphics/FrameBuffer.h"

namespace Drivers
{
	//Framebuffer is sent via DMA, commands/simple data is sent with SPI polling.
	class St7789
	{
	public:
		static void OnTransferComplete(void* arg);

		St7789(DirectDataChannel& channel, Sys::DmaStream& dmaStream, Sys::GpioPin& dcPin, Sys::GpioPin& resetPin);

		void Init();
		void Write(Graphics::FrameBuffer& framebuffer);

	private:
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

		void OnTransferComplete();

		//NOTE(tsharpe): This method doesn't allow for offsets
		void SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
		void SendCommand(Command command);
		void SendData(uint8_t data);
		void SendData(const uint8_t* buffer, size_t length);
		void SendDataDMA(const uint16_t* buffer, size_t length);

		DirectDataChannel& m_channel;
		Sys::DmaStream& m_dmaStream;
		Sys::GpioPin& m_dcPin;
		Sys::GpioPin& m_resetPin;
		Rtos::KEvent m_event;

		size_t m_xOffset;
		size_t m_yOffset;
	};
}
