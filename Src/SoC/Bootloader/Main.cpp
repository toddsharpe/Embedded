#include "Assert.h"
#include "SoC/Boards/Basys3.h"

using namespace SoC;

//Tasks
extern void DisplayTask();

int main()
{
	//Init Board
	Board::Init();
	Board::Printf("Bootloader Active\r\n");

	DisplayTask();
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

	while (1);
}