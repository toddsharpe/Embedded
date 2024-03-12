#include "Assert.h"
#include "Stm32/Boards/Disco-F746GNG.h"
#include "Sys/IsrVector.h"
#include "Sys/SystemTimer.h"
#include "Rtos/Kernel.h"

using namespace Stm32;
using namespace Rtos;

//Tasks
extern void AliveTask();
extern void DisplayTask();

void RxReceived(void* arg)
{
	ReadOnlyBuffer buffer = Board::uart.Read();
	Board::Printf("Received: %s\r\n", buffer.Data);
}

int main(void)
{
	//Init board
	Board::Init();
	SystemTimer::Init(Board::GetSysClkFreq(), SystemTimer::TickFreq_100HZ);
	Board::Printf("Application Active\r\n");

	//Init kernel
	Rtos::Init();
	IsrVector::Register(IRQn_Type::SysTick_IRQn, {&Rtos::OnSysTick, nullptr});

	//Initialize Uart RX
	IsrVector::Register(Board::uart.GetInterupt(), {&Usart::OnInterupt, &Board::uart});
	Board::uart.EnableRx();
	Board::uart.DgramReceived = { nullptr, RxReceived };

	//Create threads
	Rtos::CreateThread(&AliveTask);
	Rtos::CreateThread(&DisplayTask);
	Rtos::Run();
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

	Rtos::Stop();
	while (1);
}
