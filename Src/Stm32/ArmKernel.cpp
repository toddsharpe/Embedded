#include "Rtos/Types.h"
#include "Rtos/KThread.h"
#include "Rtos/Scheduler.h"
#include "Rtos/Kernel.h"

#include <Arm.h>
#include <stm32f746xx.h>

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
		return sizeof(ArmContext);
	}
	
	void KThread::InitContext(void *stack, ThreadStart entry)
	{
		new (stack) ArmContext((void *)entry, (void *)&KThread::Idle);
	}

	void Scheduler::Reschedule()
	{
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	}

	void Kernel::Start()
	{
		__asm("SVC 0");
		KThread::Idle();
	}
}
