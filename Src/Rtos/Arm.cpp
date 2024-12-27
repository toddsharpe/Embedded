#include "Buffer.h"
#include "Rtos/KThread.h"
#include "Rtos/Kernel.h"

#include <Arm.h>
#if defined(STM32F746xx)
	#include <stm32f746xx.h>
#else
	#include "stm32f401xc.h"
#endif

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

	void RequestReschedule()
	{
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	}

	void Start()
	{
		__asm("SVC 0");
		KThread::Idle();
	}
}
