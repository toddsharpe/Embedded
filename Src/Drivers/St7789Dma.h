// DOC: St7789.pdf

#pragma once

#include "Rtos/Types.h"
#include "Sys/GpioPin.h"
#include "DirectOutputChannel.h"
#include "Sys/DmaStream.h"
#include "Rtos/KEvent.h"
#include "Graphics/FrameBuffer.h"
#include "Drivers/St7789Base.h"

namespace Drivers
{
	//Framebuffer is sent via DMA, commands/simple data is sent with SPI polling.
	class St7789Dma : public St7789Base
	{
	public:
		static void OnTransferComplete(void* arg);

		St7789Dma(DirectOutputChannel& channel, Sys::GpioPin& dcPin, Sys::GpioPin& resetPin, Sys::DmaStream& dmaStream);

		virtual void Init() override;
		void Write(Graphics::FrameBuffer& framebuffer);

	private:
		void OnTransferComplete();
		void SendDataDMA(const uint16_t* buffer, size_t length);

		Sys::DmaStream& m_dmaStream;
		void* const m_dmaWriteAddress;
		Rtos::KEvent m_event;
	};
}
