#include "Inc/Arm.h"
#include "Stm32/GpioPin.h"
#include "Stm32/SystemTimer.h"
#include "Stm32/Nucleo-F746ZG.h"
#include "Rtos/Kernel.h"
#include "Net/UdpDgramChannel.h"
#include "core_cm7.h"

#include "Stm32/System.h"
#include "OTA.h"
#include "Updater.h"

using namespace Stm32;
using namespace Rtos;
using namespace Net;

//Board and Kernel
static NucleoF746ZG board = {};
static Stm32::SystemTimer sysTimer(Sys::TickFreq::TickFreq_100HZ);
Kernel kernel(board, sysTimer);

//Updater
static StaticBuffer<1024> buffer;
static UdpDgramChannel udpChannel(OTA::Server, OTA::Port, board.ip, buffer);
static Updater updater(board, kernel, udpChannel);

void bootloader()
{
	updater.Run();
}

int main()
{
	//Init Board
	board.Init();
	sysTimer.Init(board.GetSysClkFreq());
	
	board.Printf("Bootloader Active\r\n");

	//Init kernel
	kernel.Init();
	kernel.RegisterInterrupt(IRQn_Type::SysTick_IRQn, {&Kernel::OnSysTick, &kernel});
	kernel.RegisterInterrupt(IRQn_Type::ETH_IRQn, {&EthMac::OnInterrupt, &board.mac});
	kernel.CreateThread(&bootloader);

	kernel.Run();
}

static bool in_exception = false;
extern "C" void exception_handler(const ArmContext* context)
{
	if (in_exception)
	{
		board.Printf("Double fault\r\n");
		while (1);
	}
	in_exception = true;
	
	const int32_t irq = (__get_IPSR() & 0xFF) - 16;
	if (kernel.HandleInterrupt((IRQn_Type)irq))
	{
		in_exception = false;
		return;
	}

	if (irq == -13)
	{
		//Hard fault
		board.Printf("Hard fault\r\n");
		board.Printf("HFSR 0x%x\r\n", SCB->HFSR);
		const uint16_t ufsr = SCB->CFSR >> 16;
		const uint8_t bfsr = (SCB->CFSR >> 8) & 0xFF;
		const uint8_t mfsr = SCB->CFSR & 0xFF;
		board.Printf("ufsr 0x%x, bfsr 0x%x, mfsr 0x%x\r\n", ufsr, bfsr, mfsr);
	}

	//Unhandled interrupt
	board.Printf("Unhandled interrupt\r\n");
	board.Printf("IRQ: %d, Context: [0x%08x-0x%08x]\r\n", irq, context, (uintptr_t)context + sizeof(ArmContext));
	context->Print(board);
	Bugcheck(__FILE__, STR(__LINE__), "Unhandled");
}

void ThreadSleep(const milli_t ms)
{
	kernel.Sleep(ms);
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
	board.PrintBytes(buffer, length);
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
