#include "Assert.h"
#include "HiFive/HiFive.h"
#include "HiFive/HiFive1RevB.h"
#include "HiFive/SystemTimer.h"
#include "Rtos/Kernel.h"

#define METAL_MCAUSE_CAUSE 0x000003FFUL

using namespace RiscV;
using namespace HiFive;
using namespace Rtos;

HiFive1RevB board = {};
SystemTimer sysTimer(Sys::TickFreq::TickFreq_10HZ);
Kernel kernel(board, sysTimer);

extern "C" void handler_table_entry(); 
extern "C" void MSIP_HANDLER(void* arg);

void AliveTask()
{
	board.Printf("AliveTask\r\n");
	board.LedRed.Set(false);

	while (true)
	{
		board.LedRed.Set(true);
		kernel.Sleep(500);

		board.LedRed.Set(false);
		kernel.Sleep(500);
	}
}

void AliveTask2()
{
	board.LedGreen.Set(false);

	while (true)
	{
		board.LedGreen.Set(true);
		kernel.Sleep(150);

		board.LedGreen.Set(false);
		kernel.Sleep(150);
	}
}

void AliveTask3()
{
	board.LedBlue.Set(false);

	while (true)
	{
		board.LedBlue.Set(true);
		kernel.Sleep(250);

		board.LedBlue.Set(false);
		kernel.Sleep(250);
	}
}

extern "C" uint32_t exception_handler(const uint32_t mcause, RiscV::Context* context);

int main(void)
{
	// Init Board
	board.Init();
	DebugPrintf("SysClk: %d\r\n", board.GetSysClkFreq());
	sysTimer.Init(board.GetSysClkFreq());

	// enable interrupts
	WriteMtvec((uint32_t)&handler_table_entry);

	//Enable software interrupts
	MIE mie;
	mie.AsUint32 = ReadMIE();
	mie.MSIE = 1;
	WriteMIE(mie.AsUint32);

	kernel.Init();
	kernel.RegisterInterrupt(Interrupts::MachineTimerInterrupt, {&Kernel::OnSysTick, &kernel});

	board.Printf("Application Active\r\n");

	kernel.CreateThread(&AliveTask);
	kernel.CreateThread(&AliveTask2);
	kernel.CreateThread(&AliveTask3);
	kernel.Run();
	Assert(false);
}

extern "C" uint32_t exception_handler(const uint32_t mcause, RiscV::Context* context)
{
	const uint32_t irq = mcause & METAL_MCAUSE_CAUSE;
	if (mcause & 0x80000000)
	{
		//Interrupt
		//board.Printf("Irq: %d\r\n", irq);
		if (irq == 3)
		{
			CLINT->msip = 0;
			return (uint32_t)kernel.PendSV_Handler((void*)context);
		}
		else
		{
			if (kernel.HandleInterrupt((IRQn_Type)irq))
				return (uint32_t)context;

			//Unhandled interrupt
			board.Printf("Unhandled interrupt\r\n");
			board.Printf("IRQ: %d\r\n", irq);
			context->Print(board);
			Assert(false);
			return 0;
		}
	}
	else
	{
		//syncronous
	}

	return (uint32_t)context;
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
