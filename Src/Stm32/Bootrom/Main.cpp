#include "Stm32/Nucleo-F746ZG.h"
#include "Stm32/SystemTimer.h"
#include "Rtos/Kernel.h"
#include "Arm.h"
#include "Stm32/System.h"

using namespace Stm32;
using namespace Rtos;
using namespace Net;

//Board and Kernel
static NucleoF746ZG board = {};

int main()
{
	//Init Board
	board.Init();

	board.Printf("Bootrom Active\r\n");

	//Load bootloader 0
	ResetVectorTable* isr_vector = (ResetVectorTable*)Addresses::Boot0;
	if (isr_vector->Reset >= Sector0 && isr_vector->Reset < FlashEnd)
	{
		AppMain main = (AppMain)isr_vector->Reset;
		__set_MSP(isr_vector->InitialSP);
		main();
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
