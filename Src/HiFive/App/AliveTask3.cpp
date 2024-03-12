#include "HiFive/Boards/HiFive1RevB.h"
#include "Rtos/Kernel.h"

void AliveTask3()
{
	Board::Printf("AliveTask3\r\n");
	Board::LedBlue.Set(false);

	while (true)
	{
		Board::LedBlue.Set(true);
		Rtos::SleepThread(250);

		Board::LedBlue.Set(false);
		Rtos::SleepThread(250);
	}
}
