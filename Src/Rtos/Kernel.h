#pragma once

#include "Board.h"
#include "Rtos/Types.h"
#include "Rtos/KThread.h"
#include "Rtos/Scheduler.h"
#include "KEvent.h"

#include <vector>
#include <map>
#include <list>
#include <limits>

namespace Rtos
{
	class Kernel
	{
	public:
		static void OnSysTick(void *arg);

		Kernel(Board &board, Sys::SystemTimer &sysTimer);

		bool Init();
		void Run();

		bool Stop();

		bool CreateThread(const ThreadStart entry, const ThreadPriority priority = ThreadPriority::Normal, const size_t stackSize = DefaultStackSize);

		void Yield();

		void Sleep(const size_t ms);

		void RegisterInterrupt(const InterruptVector interrupt, const InterruptContext &context);
		bool HandleInterrupt(const InterruptVector interrupt);

		WaitStatus KeWait(KSignalObject &object, const milli_t timeout = std::numeric_limits<milli_t>::max());
		void KeSignal(KEvent &event);

		void GetStats(KernelStats &stats);

		void *PendSV_Handler(void *psp);
		void *GetCurrentPSP();

	//ArchKernel
	private:
		void Start();

	private:
		static constexpr size_t DefaultStackSize = 2 * 1024;

		void OnSysTick();

		Board &m_board;
		Sys::SystemTimer &m_sysTimer;
		Scheduler m_scheduler;
		std::map<InterruptVector, InterruptContext> m_interruptHandlers;
	};
}
