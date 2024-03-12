#include "Assert.h"
#include "Board.h"
#include "Sys/SystemTimer.h"
#include "Rtos/Kernel.h"
#include "Rtos/KSleep.h"

#include <vector>
#include <list>
#include <limits>

namespace
{
	struct Wait
	{
		Rtos::KThread *Thread;
		milli_t Deadline;
	};
}

namespace Rtos
{
	static size_t m_threadIndex;
	static std::vector<KThread*> m_threads;
	static std::map<KSignalObject*, std::list<Wait>> m_signalWaits;

	static WaitStatus ObjectWait(KSignalObject &object, const milli_t timeout)
	{
		AssertOp(m_threadIndex, <, m_threads.size());
		AssertEqual(m_threads[m_threadIndex]->m_state, ThreadState::Running);
		KThread *current = m_threads[m_threadIndex];

		if (object.IsSignalled())
			return WaitStatus::Signaled;

		const milli_t deadline = SystemTimer::GetTicks() + timeout;
		current->m_state = ThreadState::SignalWait;
		m_signalWaits[&object].push_back({current, deadline});
		RequestReschedule();

		current = m_threads[m_threadIndex];
		return current->m_waitStatus;
	}

	static void ObjectSignalled(KSignalObject &object)
	{
		Assert(object.IsSignalled());

		if (!m_signalWaits[&object].size())
			return;

		// Ready threads waiting on object
		for (auto &wait : m_signalWaits[&object])
		{
			KThread *thread = wait.Thread;
			thread->m_waitStatus = WaitStatus::Signaled;
			thread->m_state = ThreadState::Ready;
		}
		m_signalWaits[&object].clear();
		m_signalWaits.erase(&object);
	}

	static bool ObjectSignalledOne(KSignalObject &object)
	{
		if (object.GetType() != KObjectType::Semaphore)
			Assert(object.IsSignalled());

		if (!m_signalWaits[&object].size())
			return false;

		const Wait &wait = m_signalWaits[&object].front();
		m_signalWaits[&object].pop_front();
		KThread *thread = wait.Thread;
		thread->m_waitStatus = WaitStatus::Signaled;
		thread->m_state = ThreadState::Ready;
		return true;
	}

	bool Init()
	{
		Board::Printf("Kernel::Init\r\n");

		// Create Idle Thread
		if (!CreateThread(&KThread::Idle, ThreadPriority::Low))
			return false;

		return true;
	}

	void Run()
	{
		//Board::Printf("Kernel::Run\r\n");
		Display();
		SystemTimer::Start();
		Start();
	}

	bool Stop()
	{
		SystemTimer::Stop();

		return true;
	}

	void Display()
	{
		for (size_t i = 0; i < m_threads.size(); i++)
		{
			Board::Printf("Thread[%d] = 0x%x, %d\r\n", i, m_threads[i]->m_stack, m_threads[i]->m_state);
		}
	}

	bool CreateThread(const ThreadStart entry, const ThreadPriority priority, const size_t stackSize)
	{
		//Board::Printf("Kernel::CreateThread\r\n");

		KThread *thread = new KThread();
		uint8_t *stack = new uint8_t[stackSize];
		thread->Init(stack, stackSize, entry);
		thread->m_priority = priority; 
		//Board::Printf("    Addr: 0x%x, Stack: [0x%x-0x%x]\r\n", thread, thread->m_stack, (uintptr_t)thread->m_stack + stackSize);

		//Add thread
		thread->m_state = ThreadState::Ready;
		m_threads.push_back(thread);

		return true;
	}

	void YieldThread()
	{
		RequestReschedule();
	}

	void SleepThread(const size_t ms)
	{
		AssertOp(m_threadIndex, <, m_threads.size());
		AssertEqual(m_threads[m_threadIndex]->m_state, ThreadState::Running);

		KSleep sleep;
		WaitStatus status = ObjectWait(sleep, ms);
		AssertEqual(status, WaitStatus::Timeout);
	}

	WaitStatus KeWait(KSignalObject &object, const milli_t timeout)
	{
		WaitStatus status = ObjectWait(object, timeout);

		switch (object.GetType())
		{
		case KObjectType::Event:
		{
			KEvent &event = (KEvent &)object;
			if (!event.IsManual())
				event.Reset();
		}
		break;

		case KObjectType::Semaphore:
		case KObjectType::Sleep:
			break;
		}

		return status;
	}

	void KeSignal(KEvent &event)
	{
		event.Set();
		if (event.IsManual())
		{
			ObjectSignalled(event);
		}
		else
		{
			if (ObjectSignalledOne(event))
				event.Reset();
		}
	}

	void SelectNextThread()
	{
		// Promote timeouts/sleeps off queue
		if (!m_signalWaits.empty())
		{
			for (auto &pair : m_signalWaits)
			{
				// Loop through waits
				auto it = pair.second.begin();
				while (it != pair.second.end())
				{
					Wait &item = *it;
					if (item.Deadline <= SystemTimer::GetTicks())
					{
						KThread *thread = item.Thread;
						Assert(thread);
						thread->m_waitStatus = WaitStatus::Timeout;
						thread->m_state = ThreadState::Ready;
						it = pair.second.erase(it);
					}
					else
					{
						it++;
					}
				}
			}
		}

		KThread *current = m_threads[m_threadIndex];
		if (current->m_state == ThreadState::Running)
			current->m_state = ThreadState::Ready;

		// Select new thread
		while (true)
		{
			m_threadIndex = (m_threadIndex + 1) % m_threads.size();

			if (m_threads[m_threadIndex]->m_state == ThreadState::Ready)
				break;
		}

		KThread *next = m_threads[m_threadIndex];
		next->m_state = ThreadState::Running;
	}

	void *GetCurrentStack()
	{
		// TODO(tsharpe): This function side-effect is a hack for the call to this function with the boot thread (SVC_Handler)
		m_threads[m_threadIndex]->m_state = ThreadState::Running;
		return m_threads[m_threadIndex]->m_stack;
	}

	void *ThreadSwap(void * const psp)
	{
		//Save current stack pointer
		m_threads[m_threadIndex]->m_stack = psp;

		SelectNextThread();
		return GetCurrentStack();
	}

	void OnSysTick(void* arg)
	{
		SystemTimer::OnTick();
		RequestReschedule();
	}

	void GetStats(KernelStats &stats)
	{
		stats.Threads = m_threads.size();
		stats.SysTicks = SystemTimer::GetTicks();
	}
}
