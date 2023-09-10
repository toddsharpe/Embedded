#include "Assert.h"
#include "Rtos/Kernel.h"

#include <vector>
#include <map>
#include <list>
#include <limits>

namespace Rtos
{
	void Kernel::OnSysTick(void *arg) { ((Kernel *)arg)->OnSysTick(); };

	Kernel::Kernel(Board &board, Sys::SystemTimer &sysTimer) : m_board(board),
														  m_sysTimer(sysTimer),
														  m_scheduler(m_sysTimer),
														  m_interruptHandlers()
	{
	}

	bool Kernel::Init()
	{
		m_board.Printf("Kernel::Init\r\n");

		// Create Idle Thread
		if (!CreateThread(&KThread::Idle, ThreadPriority::Low))
			return false;

		return true;
	}

	void Kernel::Run()
	{
		m_board.Printf("Kernel::Run\r\n");
		m_scheduler.Display();
		m_sysTimer.Start();
		this->Start();
	}

	bool Kernel::Stop()
	{
		m_sysTimer.Stop();

		return true;
	}

	bool Kernel::CreateThread(const ThreadStart entry, const ThreadPriority priority, const size_t stackSize)
	{
		m_board.Printf("Kernel::CreateThread\r\n");

		KThread *thread = new KThread();
		uint8_t *stack = new uint8_t[stackSize];
		thread->Init(stack, stackSize, entry);
		thread->m_priority = priority; 
		m_board.Printf("    Addr: 0x%x, Stack: [0x%x-0x%x]\r\n", thread, thread->m_stack, (uintptr_t)thread->m_stack + stackSize);
		m_scheduler.AddThread(*thread);

		return true;
	}

	void Kernel::Yield()
	{
		m_scheduler.Reschedule();
	}

	void Kernel::Sleep(const size_t ms)
	{
		m_scheduler.Sleep(ms);
	}

	void Kernel::RegisterInterrupt(const InterruptVector interrupt, const InterruptContext &context)
	{
		Assert(m_interruptHandlers.find(interrupt) == m_interruptHandlers.end());
		m_interruptHandlers.insert({interrupt, context});
	}

	bool Kernel::HandleInterrupt(const InterruptVector interrupt)
	{
		const auto &it = m_interruptHandlers.find(interrupt);
		if (it == m_interruptHandlers.end())
			return false;

		InterruptContext ctx = it->second;
		ctx.Handler(ctx.Context);
		return true;
	}

	WaitStatus Kernel::KeWait(KSignalObject &object, const milli_t timeout)
	{
		WaitStatus status = m_scheduler.ObjectWait(object, timeout);

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

	void Kernel::KeSignal(KEvent &event)
	{
		event.Set();
		if (event.IsManual())
		{
			m_scheduler.ObjectSignalled(event);
		}
		else
		{
			if (m_scheduler.ObjectSignalledOne(event))
				event.Reset();
		}
	}

	void Kernel::GetStats(KernelStats &stats)
	{
		stats.Threads = m_scheduler.GetThreadCount();
		stats.SysTicks = m_sysTimer.GetTicks();
	}

	void *Kernel::GetCurrentPSP()
	{
		return m_scheduler.GetCurrentPSP();
	}

	void *Kernel::PendSV_Handler(void *psp)
	{
		m_scheduler.SaveCurrentPSP(psp);
		m_scheduler.SelectNextThread();
		return m_scheduler.GetCurrentPSP();
	}

	void Kernel::OnSysTick()
	{
		m_sysTimer.OnTick();
		m_scheduler.Reschedule();
	}
}
