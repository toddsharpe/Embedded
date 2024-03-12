#include "Assert.h"
#include "Stm32/Boards/Nucleo-F746ZG.h"
#include "Sys/EthMac.h"
#include "Sys/IsrVector.h"
#include "Sys/SystemTimer.h"
#include "Stm32/Usart.h"
#include "Net/IpStack.h"
#include "Rtos/Kernel.h"

using namespace Stm32;

//Tasks
extern void AliveTask();
extern void DisplayTask();
extern void EthernetTask();

void RxReceived(void* arg)
{
	ReadOnlyBuffer buffer = Board::uart.Read();
	Board::Printf("Received: %s\r\n", buffer.Data);
}

int main(void)
{
	//Init board
	Board::Init();
	EthMac::Init();
	Net::IpStack::Init();
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
	Rtos::CreateThread(&EthernetTask);

	Rtos::Run();
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

	Rtos::Stop();
	while (1);
}
