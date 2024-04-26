#include "Assert.h"
#include "Stm32/Boards/Nucleo-F746ZG.h"
#include "Sys/EthMac.h"
#include "Sys/IsrVector.h"
#include "Sys/SystemTimer.h"
#include "Stm32/I2c.h"
#include "Stm32/Usart.h"
#include "Drivers/StSafe_A110.h"
#include "Net/IpStack.h"
#include "Rtos/Kernel.h"

using namespace Stm32;
using namespace Net;
using namespace Drivers;

//Tasks
extern void AliveTask();
//extern void DisplayTask();
extern void EthernetTask();

void RxReceived(void* arg)
{
	ReadOnlyBuffer buffer = Board::uart.Read();
	Board::Printf("Received: %s\r\n", buffer.Data);
}

void CheckStSafe()
{
	const I2cConfig config
	{
		.Master = true,
		.Addr7 = true,
		.Timing = 0x10A60D20
	};

	I2c i2c(I2C1);
	i2c.Init(config);
	//i2c.Probe();

	StSafe_A110<I2c> stsafe(i2c);
	char test[] = "test";
	stsafe.Echo({test, sizeof(test)});
}

int main(void)
{
	//Init board
	Board::Init();
	EthMac::Init();
	IpStack::Init();
	SystemTimer::Init(Board::GetSysClkFreq(), SystemTimer::TickFreq_100HZ);
	Board::Printf("Application Active\r\n");

	//Init kernel
	Rtos::Init();
	IsrVector::Register(IRQn_Type::SysTick_IRQn, {&Rtos::OnSysTick, nullptr});

	//CheckStSafe();

	//Initialize Uart RX
	IsrVector::Register(Board::uart.GetInterupt(), {&Usart::OnInterupt, &Board::uart});
	Board::uart.EnableRx();
	Board::uart.DgramReceived = { nullptr, RxReceived };

	//Create threads
	Rtos::CreateThread(&AliveTask);
	//Rtos::CreateThread(&DisplayTask);
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
