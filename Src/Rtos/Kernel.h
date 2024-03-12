#pragma once

#include "Rtos/Types.h"
#include "Rtos/KThread.h"
#include "KEvent.h"

#include <map>
#include <limits>

namespace Rtos
{
	static constexpr size_t DefaultStackSize = 2 * 1024;

	bool Init();
	void Run();
	bool Stop();
	void Display();

	bool CreateThread(const ThreadStart entry, const ThreadPriority priority = ThreadPriority::Normal, const size_t stackSize = DefaultStackSize);
	void YieldThread();
	void SleepThread(const size_t ms);

	WaitStatus KeWait(KSignalObject &object, const milli_t timeout = std::numeric_limits<milli_t>::max());
	void KeSignal(KEvent &event);

	void GetStats(KernelStats &stats);

	extern "C" void *GetCurrentStack();
	extern "C" void *ThreadSwap(void * const stack);
	void OnSysTick(void* arg);
	
	//Architecture dependent
	void Start();
	void RequestReschedule();
}
