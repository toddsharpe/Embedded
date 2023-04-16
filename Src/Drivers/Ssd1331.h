// DOC: SSD1331_1.2.pdf

#pragma once

#include "Rtos/Types.h"
#include "Sys/GpioPin.h"
#include "DirectDataChannel.h"
#include "Sys/DmaStream.h"
#include "Rtos/KEvent.h"
#include "Graphics/FrameBuffer.h"

namespace Drivers
{
	class Ssd1331
	{
	public:
		Ssd1331(DataChannel& channel, Sys::GpioPin& dcPin, Sys::GpioPin& resetPin);

		void Init();
		void Write(Graphics::FrameBuffer& framebuffer);

	private:
		static constexpr uint8_t COLOR_MODE_16bit = 0x55; // RGB565 (16bit)

		//DOC 8: Command Table
		enum Command : uint8_t
		{
			SETCOLUMN = 0x15,
			SETROW = 0x75,

			SETDISPLAYDIM = 0xAC,
			SETDISPLAYOFF = 0xAE,
			SETDISPLAYON = 0xAF,

			NORMALDISPLAY = 0xA4
		};

		//NOTE(tsharpe): This method doesn't allow for offsets
		void SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
		void SendCommand(Command command);
		void SendData(uint8_t data);
		void SendData(const uint8_t* buffer, size_t length);

		DataChannel& m_channel;
		Sys::GpioPin& m_dcPin;
		Sys::GpioPin& m_resetPin;
		Rtos::KEvent m_event;

		size_t m_xOffset;
		size_t m_yOffset;
	};
}
