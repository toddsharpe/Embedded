#include "Board.h"
#include "Arm.h"
#include "Stm32/System.h"

int main()
{
	//Init Board
	Board::Init();
	Board::Printf("Bootrom Active\r\n");

	//Load bootloader 0
	ResetVectorTable* isr_vector = (ResetVectorTable*)Addresses::Boot0;
	if (isr_vector->Reset >= Sector0 && isr_vector->Reset < FlashEnd)
	{
		AppMain main = (AppMain)isr_vector->Reset;
		__set_MSP(isr_vector->InitialSP);
		main();
	}
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
