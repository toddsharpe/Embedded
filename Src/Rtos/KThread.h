#pragma once

#include "Rtos/Types.h"

#include <cstring>
#include <cstdint>

namespace Rtos
{
	enum class ThreadState
	{
		Uninit,
		Ready,
		Running,
		SignalWait
	};

	class KThread
	{
	public:
		static void Idle();

		KThread();
		void Init(uint8_t *stack, size_t stackSize, ThreadStart entry);
	
	//ArchKernel
	private:
		static size_t GetContextSize();
		static void InitContext(void* stack, ThreadStart entry);

	public:
		void *m_stack;

		ThreadState m_state;
		ThreadPriority m_priority;
		WaitStatus m_waitStatus;
	};
}
