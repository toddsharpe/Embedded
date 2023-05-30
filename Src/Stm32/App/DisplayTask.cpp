#include "Arm.h"
#include "Rtos/Kernel.h"
#include "Stm32/DmaStream.h"
#include "Stm32/GpioPin.h"
#include "Stm32/Spi.h"
#include "Drivers/St7789Dma.h"
#include "Graphics/Color.h"
#include "Graphics/StaticFrameBuffer.h"
#include "UI/Window.h"
#include "UI/Label.h"

#include <sstream>
#include <stm32f746xx.h>

using namespace Stm32;
using namespace Rtos;

//Board and Kernel
extern Kernel kernel;

//Graphics buffer
Graphics::StaticFrameBuffer<240, 240> frameBuffer;

void DisplayTask()
{
	//SPI
	GpioPin<Port_A, 5> spi1_sck;
	GpioPin<Port_A, 7> spi1_mosi;
	spi1_sck.Init(GpioSpi1);
	spi1_mosi.Init(GpioSpi1);
	
	Spi spi1(SPI1);
	spi1.Init(SpiMode3);

	Stm32::DmaStream dmaStream(DMA2_Stream3, DMA2);
	dmaStream.Init(SPI1_TX_Stream3Channel3);
	kernel.RegisterInterrupt(dmaStream.GetInterupt(), {&Sys::DmaStream::OnInterrupt, &dmaStream});

	//Device pins
	GpioPin<Port_G, 3> dcPin;
	GpioPin<Port_G, 2> resetPin;
	dcPin.Init(GpioOutput);
	resetPin.Init(GpioOutput, true);

	//Screen
	Drivers::St7789Dma screen(spi1, dcPin, resetPin, dmaStream);
	screen.Init();

	KernelStats stats = {};
	UI::Window window("Nucleo App");
	window.Background = Graphics::Colors::Black;

	UI::Label output("Output", {5, 25, 0, 0});
	window.Children.push_back(&output);

	while (true)
	{
		kernel.GetStats(stats);

		std::stringstream ss;
		ss << "Kernel stats" << std::endl;
		ss << "  Threads: " << stats.Threads << std::endl;
		ss << " SysTicks: " << stats.SysTicks << std::endl;
		output.Text = ss.str();
		
		window.Draw(frameBuffer);
		screen.Write(frameBuffer);

		kernel.Sleep(1000);
	}
}