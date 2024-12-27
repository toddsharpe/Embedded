#include "Rtos/Kernel.h"
#include "Stm32/Boards/STEval-FCU001V2.h"

void AliveTask()
{
	Board::Printf("AliveTask\r\n");
	Board::Led1.Set(false);
	Board::Led2.Set(false);

	int counter = 0;
	while (true)
	{
		bool low = (counter & 0b01) != 0;
		bool high = (counter & 0b10) != 0;
		Board::Led1.Set(low);
		Board::Led2.Set(high);

		Rtos::SleepThread(500);

		counter = (counter + 1) % 4;
		//if (counter % 10 == 0)
			//Board::Printf("C: 0x%x\n", counter);
	}
}
