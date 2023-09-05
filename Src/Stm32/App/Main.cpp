#include "Arm.h"
#include "Stm32/GpioPin.h"
#include "Stm32/SystemTimer.h"
#include "Stm32/Nucleo-F746ZG.h"
#include "Rtos/Kernel.h"

using namespace Stm32;
using namespace Rtos;

//Board and Kernel
NucleoF746ZG board = {};
Stm32::SystemTimer sysTimer(Sys::TickFreq::TickFreq_100HZ);
Kernel kernel(board, sysTimer);

//Tasks
extern void DisplayTask();
extern void EthernetTask();
void AliveTask()
{
	board.Led1.Set(false);

	while (true)
	{
		board.Led1.Toggle();
		kernel.Sleep(1000);
	}
}

int main(void)
{
	board.Init();
	sysTimer.Init(board.GetSysClkFreq());
	kernel.Init();

	kernel.RegisterInterrupt(IRQn_Type::SysTick_IRQn, {&Kernel::OnSysTick, &kernel});
	kernel.RegisterInterrupt(board.uart.GetInterupt(), {&Usart::OnInterrupt, &board.uart});
	kernel.RegisterInterrupt(IRQn_Type::ETH_IRQn, {&EthMac::OnInterrupt, &board.mac});

	board.Printf("Application Active\r\n");

	kernel.CreateThread(&AliveTask);

	//NOTE(tsharpe): SPI MOSI and ETH MII_RX_DV share A7 and are exclusive on Nucleo144
	//See: https://os.mbed.com/teams/ST/wiki/Nucleo-144pins-ethernet-spi-conflict
	//kernel.CreateThread(&DisplayTask);
	kernel.CreateThread(&EthernetTask);

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

void DebugPrintBytes(const char* buffer, const size_t length)
{
	board.uart.PrintBytes(buffer, length);
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

void ThreadSleep(const milli_t ms)
{
	kernel.Sleep(ms);
}
