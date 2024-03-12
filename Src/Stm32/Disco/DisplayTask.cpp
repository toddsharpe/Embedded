#include "Arm.h"
#include "Stm32/Boards/Disco-F746GNG.h"
#include "Graphics/Color.h"
#include "Graphics/StaticFrameBuffer.h"
#include "Rtos/Kernel.h"
#include "UI/Window.h"
#include "UI/Label.h"
#include "UI/ProgressBar.h"

namespace
{
	Graphics::StaticFrameBuffer<Board::DisplayWidth, Board::DisplayHeight> frameBuffer;
}

void DisplayTask()
{
	Board::Printf("DisplayTask\r\n");

	UI::Window window("Disco App");
	window.Background = Graphics::Colors::Black;

	UI::Label output("Output", {5, 25, 0, 0});
	window.Children.push_back(&output);

	UI::ProgressBar progressBar("Progress", { 25, 200, 400, 20 });
	progressBar.Foreground = Graphics::Colors::Red;
	progressBar.Background = Graphics::Colors::Black;
	progressBar.InactiveColor = Graphics::Colors::White;
	progressBar.Value = 0;
	progressBar.MaxValue = 100;
	window.Children.push_back(&progressBar);

	Board::ltdc.Init();
	Board::ltdc.Layers[0].Init(frameBuffer);
	Board::ltdc.Layers[0].Enable();
	Board::ltdc.Enable();

	KernelStats stats = {};
	while (true)
	{
		Rtos::GetStats(stats);

		char buffer[256] = {};
		snprintf(buffer, sizeof(buffer), "Kernel stats\n  Threads: %ld\n SysTicks: %ld\n", stats.Threads, stats.SysTicks);
		output.Text = buffer;

		window.Draw(frameBuffer);

		progressBar.Value += 5;
		if (progressBar.Value > progressBar.MaxValue)
			progressBar.Value = 0;
		Rtos::SleepThread(500);
	}
}
