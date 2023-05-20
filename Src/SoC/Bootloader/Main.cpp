#include "SoC/Basys3.h"
#include "SoC/GpioPin.h"
#include "SoC/Spi.h"
#include "Rtos/Types.h"
//#include "Drivers/Ssd1331.h"
#include "Drivers/St7789.h"
#include "Graphics/Color.h"
#include "Graphics/StaticFrameBuffer.h"
#include "UI/Window.h"
#include "UI/Label.h"

using namespace SoC;

//Board and Kernel
Basys3 board = {};

//Graphics buffer
Graphics::StaticFrameBuffer<240, 240> frameBuffer;

int main()
{
	//Init Board
	board.Init();
	board.Printf("Bootloader Active\r\n");

	//Display screen SPI
	Spi spi1(SPI1);
	
	//Display screen pins
	GpioPin<0> dcPin;
	GpioPin<1> resetPin;
	dcPin.Init(GpioOutput);
	resetPin.Init(GpioOutput, true);

	//Screen
	Drivers::St7789 screen(spi1, dcPin, resetPin);
	screen.Init();

	UI::Window window("SoC App");
	window.Background = Graphics::Colors::Black;

	UI::Label output("Hello SoC!", {5, 25, 0, 0});
	output.Foreground = Graphics::Colors::Red;
	window.Children.push_back(&output);

	window.Draw(frameBuffer);
	screen.Write(frameBuffer);
}

//NOTE(tsharpe): This uses SocBlock directly, versus a kernel call
void ThreadSleep(const milli_t ms)
{
	milli_t current = SOC_BLOCK->cycles * 1000 / SOC_BLOCK->freq;
	const milli_t stop = current + ms;
	while (current < stop)
	{
		current = SOC_BLOCK->cycles * 1000 / SOC_BLOCK->freq;
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