#include "SoC/Basys3.h"

using namespace SoC;

//Board and Kernel
Basys3 board = {};

int main()
{
	//Init Board
	board.Init();

	board.Printf("Bootloader Active\r\n");

	while (1);
}

void DebugPrintf(const char* format, ...)
{
	va_list args;

	va_start(args, format);
	board.Printf(format, args);
	va_end(args);
}

void Bugcheck(const char* file, const char* line, const char* format, ...)
{
	board.Printf("Kernel Bugcheck\r\n");
	board.Printf("\r\n%s\r\n%s\r\n", file, line);

	va_list args;
	va_start(args, format);
	board.Printf(format, args);
	board.Printf("\r\n");
	va_end(args);

	while (1);
}