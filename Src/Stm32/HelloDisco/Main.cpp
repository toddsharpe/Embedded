#include "Arm.h"
#include "Stm32/GpioPin.h"
#include "Stm32/SystemTimer.h"
#include "Stm32/Disco-F746GNG.h"
#include "Rtos/Kernel.h"
#include "Graphics/StaticFrameBuffer.h"
#include "UI/Window.h"
#include "UI/Label.h"
#include "UI/ProgressBar.h"

#include <sstream>

using namespace Stm32;
using namespace Rtos;

//Board and Kernel
DiscoF746GNG board = {};
Stm32::SystemTimer sysTimer(Sys::TickFreq::TickFreq_100HZ);
Kernel kernel(board, sysTimer);

//Tasks
void HeartbeatTask()
{
	board.Printf("AliveTask\r\n");

	while (true)
	{
		board.Printf("Heartbeat\r\n");
		kernel.Sleep(5000);
	}
}

Graphics::StaticFrameBuffer<DiscoF746GNG::ScreenWidth(), DiscoF746GNG::ScreenHeight()> frameBuffer;
void DisplayTask()
{
	board.Printf("DisplayTask\r\n");

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

	board.ltdc.Init();
	board.ltdc.Layers[0].Init(frameBuffer);
	board.ltdc.Layers[0].Enable();
	board.ltdc.Enable();

	KernelStats stats = {};
	while (true)
	{
		kernel.GetStats(stats);

		std::stringstream ss;
		ss << "Kernel stats" << std::endl;
		ss << "  Threads: " << stats.Threads << std::endl;
		ss << " SysTicks: " << stats.SysTicks << std::endl;
		output.Text = ss.str();
		window.Draw(frameBuffer);

		progressBar.Value += 5;
		if (progressBar.Value > progressBar.MaxValue)
			progressBar.Value = 0;
		kernel.Sleep(500);
	}
}

int main(void)
{
	board.Init();
	sysTimer.Init(board.GetSysClkFreq());
	kernel.Init();

	kernel.RegisterInterrupt(IRQn_Type::SysTick_IRQn, {&Kernel::OnSysTick, &kernel});
	kernel.RegisterInterrupt(board.uart.GetInterupt(), {&Usart::OnInterrupt, &board.uart});

	board.Printf("Application Active\r\n");

	kernel.CreateThread(&HeartbeatTask);
	kernel.CreateThread(&DisplayTask);
	kernel.Run();
}

extern "C" void exception_handler(const ArmContext* context)
{
	const uint32_t irq = (__get_IPSR() & 0xFF) - 16;
	if (kernel.HandleInterrupt((IRQn_Type)irq))
		return;

	//Unhandled interrupt
	board.Printf("Unhandled interrupt\r\n");
	board.Printf("IRQ: %d\r\n", irq);
	context->Print(board);
	Assert(false);
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

	kernel.Stop();
	while (1);
}