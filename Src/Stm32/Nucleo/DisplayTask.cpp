#include "Arm.h"
#include "Board.h"
#include "Rtos/Kernel.h"
#include "Stm32/DmaStream.h"
#include "Stm32/GpioPin.h"
#include "Stm32/Spi.h"
#include "Drivers/St7789_Dma.h"
#include "Sys/IsrVector.h"
#include "Graphics/Color.h"
#include "Graphics/StaticFrameBuffer.h"
#include "UI/Window.h"
#include "UI/Label.h"

#include <stm32f746xx.h>

using namespace Stm32;
using namespace Rtos;
using namespace Graphics;

namespace
{
	Graphics::StaticFrameBuffer<240, 240> frameBuffer;
}

void DisplayTask()
{
	Board::Printf("DisplayTask\r\n");
	
	//SPI
	Spi spi(SPI1);
	spi.Init(SpiMode3);

	Stm32::DmaStream dmaStream(DMA2_Stream3, DMA2);
	dmaStream.Init(SPI1_TX);
	IsrVector::Register(dmaStream.GetInterupt(), {&DmaStream::OnInterrupt, &dmaStream});

	//Device pins
	GpioPin dcPin(GPIOG, 3);
	dcPin.Init(GpioOutput);
	GpioPin resetPin(GPIOG, 2);
	resetPin.Init(GpioOutput, true);

	//Screen
	Drivers::St7789_Dma<Spi, GpioPin, DmaStream> screen(spi, dcPin, resetPin, dmaStream);
	screen.Init();

	KernelStats stats = {};
	UI::Window window("Nucleo App");
	window.Background = Colors::Black;

	UI::Label output("Output", {5, 25, 0, 0});
	window.Children.push_back(&output);

	while (true)
	{
		Rtos::GetStats(stats);

		char buffer[256] = {};
		snprintf(buffer, sizeof(buffer), "Kernel stats\n  Threads: %ld\n SysTicks: %ld\n", stats.Threads, stats.SysTicks);
		output.Text = buffer;
		
		window.Draw(frameBuffer);
		screen.Write(frameBuffer);

		Rtos::SleepThread(1000);
	}
}