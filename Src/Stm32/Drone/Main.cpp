#include "Board.h"
#include "Arm.h"
#include "Sys/IsrVector.h"
#include "Sys/SystemTimer.h"
#include "Stm32/System.h"
#include "Stm32/Boards/STEval-FCU001V2.h"

extern void AliveTask();

int main()
{
	//Init Board
	Board::Init();
	SystemTimer::Init(Board::GetSysClkFreq(), SystemTimer::TickFreq_10HZ);
	Board::Printf("Drone Active\r\n");

	//Set up ISR
	IsrVector::Register(IRQn_Type::SysTick_IRQn, {&SystemTimer::OnTick, nullptr});

	//Superloop
	SystemTimer::Start();
	int counter = 0;
	while (true)
	{
		bool low = (counter & 0b01) != 0;
		bool high = (counter & 0b10) != 0;
		Board::Led1.Set(low);
		Board::Led2.Set(high);

		SystemTimer::ThreadSleep(1000);
		counter = (counter + 1) % 4;
	}

	//Run
	//Rtos::Run();
	//drone();
}

void Bugcheck(const char* file, const char* line, const char* format, ...)
{
	Board::Printf("Kernel Bugcheck\r\n");
	Board::Printf("\r\n%s\r\n%s\r\n", file, line);

	va_list args;
	va_start(args, format);
	Board::PrintfVA(format, args);
	Board::Printf("\r\n");
	va_end(args);

	while (1);
}
