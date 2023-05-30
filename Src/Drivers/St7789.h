// DOC: St7789.pdf

#pragma once

#include "Sys/GpioPin.h"
#include "DataChannel.h"
#include "Graphics/FrameBuffer.h"
#include "Drivers/St7789Base.h"

namespace Drivers
{
	//Framebuffer/commands/simple data is sent with SPI polling.
	class St7789 : public St7789Base
	{
	public:
		St7789(DataChannel& channel, Sys::GpioPin& dcPin, Sys::GpioPin& resetPin);

		void Write(Graphics::FrameBuffer& framebuffer);
	};
}
