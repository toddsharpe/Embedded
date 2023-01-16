#include "HiFive/SystemTimer.h"

using namespace RiscV;

namespace HiFive
{
	SystemTimer::SystemTimer(const Sys::TickFreq freq) :
		Sys::SystemTimer(freq)
	{
	}

	void SystemTimer::Init(const uint32_t sysFreq)
	{
		//Timer isn't based on sysfreq, it's based on the mtime clock rate
		const uint32_t freq = MTIME_RATE_HZ_DEF;
		const uint32_t ticks = (freq * m_freq) / 1000U;

		//TODO(tsharpe): This is a hack to get the timer to work, doesn't work for high values of time
		CLINT->mtimecmp = CLINT->mtime + ticks;
		CLINT->mtimecmph = 0;
	}

	void SystemTimer::Start()
	{
		//Reset the timer
		Init(0);
		
		//Enable the machine timer interrupt
		MIE mie;
		mie.AsUint32 = ReadMIE();
		mie.MTIE = 1;
		WriteMIE(mie.AsUint32);
	}

	void SystemTimer::Stop()
	{
		//Disable the machine timer interrupt
		MIE mie;
		mie.AsUint32 = ReadMIE();
		mie.MTIE = 0;
		WriteMIE(mie.AsUint32);
	}

	void SystemTimer::OnTick()
	{
		Sys::SystemTimer::OnTick();

		//Reset the timer
		Init(0);
	}
}
