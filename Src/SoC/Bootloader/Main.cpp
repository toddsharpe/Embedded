#include "SoC/Basys3.h"
#include "SoC/GpioPin.h"
#include "SoC/Spi.h"
#include "Drivers/Ssd1331.h"
#include "Graphics/Color.h"
#include "Graphics/StaticFrameBuffer.h"

using namespace SoC;

//Board and Kernel
Basys3 board = {};

//Graphics buffer
//Graphics::StaticFrameBuffer<96, 64> frameBuffer;

int main()
{
	//Init Board
	board.Init();
	board.Printf("Bootloader Active\r\n");

/*
	//Write to frame
	{
		frameBuffer.DrawText({0, 0}, "Hello World", Graphics::Colors::Red);
	}

	//Write to display
	{
		GpioPin<0> dcPin;
		dcPin.Init(GpioOutput);
		GpioPin<1> resetPin;
		resetPin.Init(GpioOutput, true);
		GpioPin<1> vccenPin;
		vccenPin.Init(GpioOutput);
		GpioPin<1> pmodenPin;
		pmodenPin.Init(GpioOutput);

		Spi spi1(SPI1);
		spi1.Init();

		//Screen
		Drivers::Ssd1331 screen(spi1, dcPin, resetPin);
		screen.Init();

	}
*/

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