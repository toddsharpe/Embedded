// DOC: St7789.pdf

#include "Assert.h"
#include "Drivers/St7789.h"
#include "Rtos/Types.h"

extern void ThreadSleep(const milli_t ms);

namespace Drivers
{
	St7789::St7789(OutputChannel &channel, Sys::GpioPin &dcPin, Sys::GpioPin &resetPin) :
		St7789Base(channel, dcPin, resetPin)
	{
	}

	void St7789::Write(Graphics::FrameBuffer &framebuffer)
	{
		// Set address
		SetAddressWindow(0, 0, framebuffer.GetWidth() - 1, framebuffer.GetHeight() - 1);

		SendData((uint8_t *)framebuffer.GetBuffer(), framebuffer.Size());
	}
}
