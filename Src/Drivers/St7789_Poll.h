// DOC: St7789.pdf

#pragma once

#include "Graphics/FrameBuffer.h"
#include "Drivers/St7789_Base.h"

namespace Drivers
{
	//Framebuffer/commands/simple data is sent with SPI polling.
	template <class TChannel, class TGpio>
	class St7789_Poll : public St7789_Base<TChannel, TGpio>
	{
	public:
		typedef St7789_Base<TChannel, TGpio> Base;

		St7789_Poll(TChannel& channel, TGpio& dcPin, TGpio& resetPin) :
			St7789_Base<TChannel, TGpio>(channel, dcPin, resetPin)
		{}

		void Write(Graphics::FrameBuffer& framebuffer)
		{
			// Set address
			Base::SetAddressWindow(0, 0, framebuffer.GetWidth() - 1, framebuffer.GetHeight() - 1);

			Base::SendData((uint8_t *)framebuffer.GetBuffer(), framebuffer.Size());
		}
	};
}
