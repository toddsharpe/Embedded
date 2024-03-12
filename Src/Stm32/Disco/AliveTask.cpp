#include "Rtos/Kernel.h"
#include "Stm32/Boards/Disco-F746GNG.h"

void AliveTask()
{
	Board::Printf("AliveTask\r\n");

	while (true)
	{
		Board::Printf("Heartbeat\r\n");
		Rtos::SleepThread(1000);
	}
}
