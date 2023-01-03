#include "KThread.h"

#include <cstring>
#include <cstdint>

namespace Rtos
{
	KThread::KThread() : m_stack(),
						 m_state(ThreadState::Uninit),
						 m_priority(ThreadPriority::Normal),
						 m_waitStatus(WaitStatus::None)
	{
	}

	void KThread::Init(uint8_t *stack, size_t stackSize, ThreadStart entry)
	{
		stack += stackSize;

		//Push context
		stack -= GetContextSize();
		InitContext(stack, entry);

		// Save stack pointer
		m_stack = stack;
		m_state = ThreadState::Ready;
	}
}
