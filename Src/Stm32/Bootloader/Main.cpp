#include "Assert.h"
#include "Board.h"
#include "Sys/EthMac.h"
#include "Sys/IsrVector.h"
#include "Sys/SystemTimer.h"
#include "Rtos/Kernel.h"
#include "OTA.h"
#include "Stm32/System.h"
#include "Updater.h"
#include "Net/IpStack.h"
#include "Net/UdpChannel.h"

//Updater
static UdpChannel channel(OTA::Server, OTA::Port);
static Updater<UdpChannel> updater(channel);

void bootloader()
{
	//Rtos::SleepThread(5000);
	//Board::Printf("Starting Updater\r\n");
	updater.Run();
}

int main()
{
	//Init Board
	Board::Init();
	EthMac::Init();
	Net::IpStack::Init();
	channel.Init();
	SystemTimer::Init(Board::GetSysClkFreq(), SystemTimer::TickFreq_100HZ);
	Board::Printf("Bootloader Active\r\n");

	//Init kernel
	Rtos::Init();
	IsrVector::Register(IRQn_Type::SysTick_IRQn, {&Rtos::OnSysTick, nullptr});
	Rtos::CreateThread(&bootloader);

	//Run
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
