#include "Sys/SystemTimer.h"

#include <FE310.h>
#include <RiscV.h>

using namespace RiscV;

namespace SystemTimer
{
	static TickFreq m_freq;
	static uint32_t m_ticks;

	void Init(const uint32_t sysFreq, const TickFreq tickFreq)
	{
		m_freq = tickFreq;

		//Timer isn't based on sysfreq, it's based on the mtime clock rate
		const uint32_t freq = MTIME_RATE_HZ_DEF;
		const uint32_t ticks = (freq * m_freq) / 1000U;

		//TODO(tsharpe): This is a hack to get the timer to work, doesn't work for high values of time
		CLINT->mtimecmp = CLINT->mtime + ticks;
		CLINT->mtimecmph = 0;
	}

	void Start()
	{
		//Reset the timer
		Init(0, m_freq);
		
		//Enable the machine timer interrupt
		MIE mie;
		mie.AsUint32 = ReadMIE();
		mie.MTIE = 1;
		WriteMIE(mie.AsUint32);
	}

	void Stop()
	{
		//Disable the machine timer interrupt
		MIE mie;
		mie.AsUint32 = ReadMIE();
		mie.MTIE = 0;
		WriteMIE(mie.AsUint32);
	}

	void OnTick()
	{
		m_ticks += m_freq;

		//Reset the timer
		Init(0, m_freq);
	}

	uint32_t GetTicks()
	{
		return m_ticks;
	}
}
