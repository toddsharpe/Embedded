#include "HiFive/Boards/HiFive1RevB.h"
#include "Rtos/Kernel.h"

void AliveTask()
{
	Board::Printf("AliveTask\r\n");
	Board::LedRed.Set(false);

	while (true)
	{
		Board::LedRed.Set(true);
		Rtos::SleepThread(500);

		Board::LedRed.Set(false);
		Rtos::SleepThread(500);
	}
}
