#include "Arm.h"
#include "Stm32/GpioPin.h"
#include "Stm32/SystemTimer.h"
#include "Stm32/Nucleo-F746ZG.h"
#include "Rtos/Kernel.h"
#include "Drivers/Hc06.h"

#include "System.h"
#include "Updater.h"

using namespace Stm32;
using namespace Rtos;

//Board and Kernel
NucleoF746ZG board = {};
Stm32::SystemTimer sysTimer(Sys::TickFreq::TickFreq_100HZ);
Kernel kernel(board, sysTimer);

//Peripherals
Usart uart2(USART2);
Hc06 bluetooth(uart2);

//Updater
Updater updater(board, kernel, bluetooth);

void bootloader()
{
	updater.Run();
}

int main()
{
	//Init Board
	board.Init();
	sysTimer.Init(board.GetSysClkFreq());
	kernel.Init();
	kernel.RegisterInterrupt(IRQn_Type::SysTick_IRQn, {&Kernel::OnSysTick, &kernel});
	kernel.RegisterInterrupt(uart2.GetInterupt(), {&Usart::OnInterrupt, &uart2});

	//Init Peripherals
	{
		Stm32::GpioPin<Port_D, 5> uart2_tx;
		uart2_tx.Init(GpioUart2);
		Stm32::GpioPin<Port_D, 6> uart2_rx;
		uart2_rx.Init(GpioUart2);
	}
	uart2.Init(board.rcc.GetPClk1Freq(), UartDefault);
	bluetooth.Init();

	board.Printf("Bootloader Active\r\n");

	kernel.CreateThread(&bootloader);
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