#include "Assert.h"
#include "HiFive/HiFive.h"
#include "HiFive/Boards/HiFive1RevB.h"
#include "Sys/IsrVector.h"
#include "Sys/SystemTimer.h"
#include "Rtos/Kernel.h"

#include <RiscV.h>

using namespace RiscV;
using namespace HiFive;
using namespace Rtos;

//Tasks
extern void AliveTask();
extern void AliveTask2();
extern void AliveTask3();

extern "C" void Default_Handler(void);

int main(void)
{
	// Init Board
	Board::Init();
	SystemTimer::Init(Board::GetSysClkFreq(), SystemTimer::TickFreq_10HZ);
	Board::Printf("Application Active\r\n");

	// enable interrupts
	WriteMtvec((uint32_t)&Default_Handler);

	//Enable software interrupts
	MIE mie;
	mie.AsUint32 = ReadMIE();
	mie.MSIE = 1;
	WriteMIE(mie.AsUint32);

	//Init kernel
	Rtos::Init();
	IsrVector::Register(Interrupts::MachineTimerInterrupt, {&Rtos::OnSysTick, nullptr});

	//Create threads
	Rtos::CreateThread(&AliveTask);
	Rtos::CreateThread(&AliveTask2);
	Rtos::CreateThread(&AliveTask3);
	Rtos::Run();
}

void Bugcheck(const char* file, const char* line, const char* format, ...)
{
	Board::Printf("Kernel Bugcheck\r\n");
	Board::Printf("\r\n%s\r\n%s\r\n", file, line);

	va_list args;
	va_start(args, format);
	Board::Printf(format, args);
	Board::Printf("\r\n");
	va_end(args);

	Rtos::Stop();
	while (1);
}
