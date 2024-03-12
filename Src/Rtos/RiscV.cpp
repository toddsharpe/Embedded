#include "Assert.h"
#include "Board.h"
#include "Buffer.h"
#include "Rtos/KThread.h"
#include "Rtos/Kernel.h"

#include <RiscV.h>
#include <FE310.h>

using namespace RiscV;

namespace Rtos
{
	void KThread::Idle()
	{
		while (1)
		{
			__asm("WFI");
		}
	}

	size_t KThread::GetContextSize()
	{
		return sizeof(RiscV::Context);
	}

	void KThread::InitContext(void *stack, ThreadStart entry)
	{
		new (stack) Context((void *)entry, (void *)&KThread::Idle);
	}

	// https://chromitem-soc.readthedocs.io/en/latest/clint.html#msip-register
	void RequestReschedule()
	{
		CLINT->msip = 1;
	}

	void Start()
	{
		// Get first thread
		void *s = Rtos::GetCurrentStack();
		s = (void *)((uint32_t)s + sizeof(RiscV::Context));
		Board::Printf("KernelStart: %p\r\n", s);
		RiscV::Context *context = (RiscV::Context *)Rtos::GetCurrentStack();
		context->x2 = (uint32_t)context; // SP

		// Enable MPIE
		RiscV::MSTATUS mstatus;
		mstatus.AsUint32 = ReadMStatus();
		// Assert(mstatus.MIE);
		mstatus.MPIE = 1;
		// TODO(tsharpe): Set MPP to user mode
		WriteMStatus(mstatus.AsUint32);

		// Set PC
		RiscV::WriteMepc(context->PC);

		// Set registers
		__asm__ volatile("mv ra, %0" ::"r"(context->x1));
		__asm__ volatile("mv sp, %0" ::"r"(s));

		// Return
		__asm__ volatile("mret");
	}
}
