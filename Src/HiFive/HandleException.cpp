#include "Assert.h"
#include "Board.h"
#include "Rtos/Kernel.h"
#include "Sys/IsrVector.h"

#include <cstdint>
#include <RiscV.h>
#include <FE310.h>

#define METAL_MCAUSE_CAUSE 0x000003FFUL

extern "C" uint32_t HandleException(const uint32_t mcause, RiscV::Context* context)
{
	const uint32_t irq = mcause & METAL_MCAUSE_CAUSE;
	if (mcause & 0x80000000)
	{
		//Interrupt
		if (irq == 3)
		{
			CLINT->msip = 0;
			return (uint32_t)Rtos::ThreadSwap((void*)context);
		}
		else
		{
			if (IsrVector::Handle((uint8_t)irq))
				return (uint32_t)context;

			//Unhandled interrupt
			Board::Printf("Unhandled interrupt\r\n");
			Board::Printf("IRQ: %d\r\n", irq);
			Board::Printf("PC: 0x%x, X1: 0x%x, X2: 0x%x\r\n", context->PC, context->x1, context->x2);
			Bugcheck(__FILE__, STR(__LINE__), "Unhandled");
		}
	}
	else
	{
		//syncronous
	}

	return (uint32_t)context;
}
