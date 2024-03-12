#include "HiFive/Boards/HiFive1RevB.h"
#include "Rtos/Kernel.h"

void AliveTask2()
{
	Board::Printf("AliveTask2\r\n");
	Board::LedGreen.Set(false);

	while (true)
	{
		Board::LedGreen.Set(true);
		Rtos::SleepThread(150);

		Board::LedGreen.Set(false);
		Rtos::SleepThread(150);
	}
}
