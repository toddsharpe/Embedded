#pragma once


#include "Rtos/KThread.h"
#include "Rtos/KSignalObject.h"
#include "Sys/SystemTimer.h"

#include <vector>
#include <map>
#include <list>

namespace Rtos
{
	class Scheduler
	{
	public:
		Scheduler(const Sys::SystemTimer& timer);

		void AddThread(KThread& thread);
		void Sleep(const milli_t ms);

		WaitStatus ObjectWait(KSignalObject& object, const milli_t timeout);
		void ObjectSignalled(KSignalObject& object);
		bool ObjectSignalledOne(KSignalObject& object);

		void SaveCurrentPSP(void *psp);

		void *GetCurrentPSP();

		void SelectNextThread();

		size_t GetThreadCount() const;

		void Display();

		//ArchKernel
		void Reschedule();

	private:
		struct Wait
		{
			KThread *Thread;
			milli_t Deadline;
		};

		const Sys::SystemTimer& m_sysTimer;

		size_t m_threadIndex;
		std::vector<KThread*> m_threads;
		std::map<KSignalObject*, std::list<Wait>> m_signalWaits;
	};
}