#include "SoC/Basys3.h"
#include "SoC/GpioPin.h"
#include "SoC/Spi.h"
#include "SoC/SpiDmaStream.h"
#include "Rtos/Types.h"
//#include "Drivers/Ssd1331.h"
#include "Drivers/St7789Dma.h"
#include "Graphics/Color.h"
#include "Graphics/StaticFrameBuffer.h"
#include "UI/Window.h"
#include "UI/Label.h"

using namespace SoC;

//Board and Kernel
Basys3 board = {};

//Graphics buffer
Graphics::StaticFrameBuffer<240, 240> frameBuffer;

void ThreadSleep(const milli_t ms);

int main()
{
	//Init Board
	board.Init();
	board.Printf("Bootloader Active\r\n");

	//Display screen SPI and DMA
	Spi spi1(SPI1);

	SpiDmaStream dmaStream(SPI_DMA1);
	dmaStream.Init(Spi_HWrite);
	
	//Display screen pins
	GpioPin<0> dcPin;
	GpioPin<1> resetPin;
	dcPin.Init(GpioOutput);
	resetPin.Init(GpioOutput, true);

	//Screen
	Drivers::St7789Dma screen(spi1, dcPin, resetPin, dmaStream);
	screen.Init();

	UI::Window window("SoC App");
	window.Background = Graphics::Colors::Black;

	UI::Label output("Hello SoC!", {5, 25, 0, 0});
	output.Foreground = Graphics::Colors::Red;
	window.Children.push_back(&output);

	const Graphics::Color color[3] = { Graphics::Colors::Black, Graphics::Colors::Red, Graphics::Colors::Blue };
	int index = 0;

	IO_BLOCK->led_display = 0x0;
	IO_BLOCK->led_bar = 0x0;
	while (true)
	{
		window.Background = color[index];
		index = (index + 1) % 3;

		output.Foreground = color[index];
		index = (index + 1) % 3;

		window.Draw(frameBuffer);
		screen.Write(frameBuffer);
		IO_BLOCK->led_display++;
		IO_BLOCK->led_bar--;
		ThreadSleep(100);
	}
}

//NOTE(tsharpe): This uses SocBlock directly, versus a kernel call
void ThreadSleep(const milli_t ms)
{
	const milli_t stop = SOC_BLOCK->cycles + SOC_BLOCK->freq * ms / 1000;
	while (SOC_BLOCK->cycles < stop)
	{
		__asm("nop");
	}
}

void DebugPrintf(const char* format, ...)
{
	va_list args;

	va_start(args, format);
	board.Printf(format, args);
	va_end(args);
}

void Bugcheck(const char* file, const char* line, const char* format, ...)
{
	board.Printf("Kernel Bugcheck\r\n");
	board.Printf("\r\n%s\r\n%s\r\n", file, line);

	va_list args;
	va_start(args, format);
	board.Printf(format, args);
	board.Printf("\r\n");
	va_end(args);

	while (1);
}