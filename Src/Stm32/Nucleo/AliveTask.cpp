#include "Rtos/Kernel.h"
#include "Stm32/Boards/Nucleo-F746ZG.h"

void AliveTask()
{
	Board::Printf("AliveTask\r\n");
	Board::Led1.Set(false);

	while (true)
	{
		Board::Led1.Set(!Board::Led1.Get());
		Rtos::SleepThread(1000);
	}
}
