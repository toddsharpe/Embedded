#include "Arm.h"
#include "Assert.h"
#include "Board.h"
#include "Sys/IsrVector.h"

#include <stm32f746xx.h>

namespace
{
	bool in_exception = false;
	constexpr int32_t HardFault = -13;
}

extern "C" void HandleException(const ArmContext* context)
{
	if (in_exception)
	{
		Board::Printf("Double fault\r\n");
		while (1);
	}
	in_exception = true;

	const int32_t irq = (__get_IPSR() & 0xFF) - 16;
	if (IsrVector::Handle((uint8_t)irq))
	{
		in_exception = false;
		return;
	}

	if (irq == HardFault)
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