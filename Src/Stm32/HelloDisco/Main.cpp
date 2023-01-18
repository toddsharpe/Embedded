#include "Arm.h"
#include "Stm32/GpioPin.h"
#include "Stm32/SystemTimer.h"
#include "Stm32/Disco-F746GNG.h"
#include "Rtos/Kernel.h"

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
		kernel.Sleep(1000);
	}
}

void DisplayTask()
{
	board.Printf("DisplayTask\r\n");

	KernelStats stats = {};
	while (true)
	{
		kernel.GetStats(stats);

		std::stringstream ss;
		ss << "Kernel stats:\r\n";
		ss << "  Threads: " << stats.Threads << "\r\n";
		ss << " SysTicks: " << stats.SysTicks << "\r\n";
		board.Write(ss.str());

		kernel.Sleep(5000);
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