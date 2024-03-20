#include "Assert.h"
#include "Stm32/Board.h"
#include "Sys/EthMac.h"
#include "Sys/SystemTimer.h"
#include "Rtos/Kernel.h"
#include "Arm.h"
#include "OTA.h"
#include "Net/UdpDgramChannel.h"
#include "Stm32/System.h"
#include "Updater.h"

//Updater
static StaticBuffer<1200> buffer;
static Net::UdpDgramChannel udpChannel(OTA::Server, OTA::Port, buffer);
static Updater updater(udpChannel);

void bootloader()
{
	updater.Run();
}

int main()
{
	//Init Board
	Board::Init();
	EthMac::Init();
	SystemTimer::Init(Board::GetSysClkFreq(), SystemTimer::TickFreq_100HZ);
	
	Board::Printf("Bootloader Active\r\n");

	//Init kernel
	Rtos::Init();
	Rtos::RegisterInterrupt(IRQn_Type::SysTick_IRQn, {&Rtos::OnSysTick, nullptr});
	Rtos::RegisterInterrupt(IRQn_Type::ETH_IRQn, {&EthMac::OnInterrupt, nullptr});
	Rtos::CreateThread(&bootloader);

	Rtos::Run();
}

static bool in_exception = false;
extern "C" void exception_handler(const ArmContext* context)
{
	if (in_exception)
	{
		Board::Printf("Double fault\r\n");
		while (1);
	}
	in_exception = true;
	
	const int32_t irq = (__get_IPSR() & 0xFF) - 16;
	if (Rtos::HandleInterrupt((IRQn_Type)irq))
	{
		in_exception = false;
		return;
	}

	if (irq == -13)
	{
		//Hard fault
		Board::Printf("Hard fault\r\n");
		Board::Printf("HFSR 0x%x\r\n", SCB->HFSR);
		const uint16_t ufsr = SCB->CFSR >> 16;
		const uint8_t bfsr = (SCB->CFSR >> 8) & 0xFF;
		const uint8_t mfsr = SCB->CFSR & 0xFF;
		Board::Printf("ufsr 0x%x, bfsr 0x%x, mfsr 0x%x\r\n", ufsr, bfsr, mfsr);
	}

	//Unhandled interrupt
	Board::Printf("Unhandled interrupt\r\n");
	Board::Printf("IRQ: %d, Context: [0x%08x-0x%08x]\r\n", irq, context, (uintptr_t)context + sizeof(ArmContext));
	Board::Printf("PC: 0x%x, LR: 0x%x, CallerLR: 0x%x\r\n", context->HW.PC, context->SW.LR, context->HW.LR);
	Board::Printf("R4: 0x%x, R5: 0x%x, R6: 0x%x, R7: 0x%x\r\n", context->SW.R4, context->SW.R5, context->SW.R6, context->SW.R7);
	Bugcheck(__FILE__, STR(__LINE__), "Unhandled");
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
