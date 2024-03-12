#include "SoC/GpioPin.h"
#include "SoC/Spi.h"
#include "Drivers/St7789_Poll.h"
#include "Graphics/Color.h"
#include "Graphics/StaticFrameBuffer.h"
#include "UI/Window.h"
#include "UI/Label.h"

using namespace SoC;

namespace
{
	Graphics::StaticFrameBuffer<240, 240> frameBuffer;
}

void DisplayTask()
{
	//Display screen SPI
	Spi spi1(SPI1);
	
	//Display screen pins
	GpioPin dcPin(GPIO1, 0);
	GpioPin resetPin(GPIO1, 1);
	dcPin.Init(GpioOutput);
	resetPin.Init(GpioOutput, true);

	//Screen
	Drivers::St7789_Poll screen(spi1, dcPin, resetPin);
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
		Rtos::SleepThread(100);
	}
}
