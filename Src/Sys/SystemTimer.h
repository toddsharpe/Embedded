#pragma once

#include <cstdint>

namespace Sys
{
	enum TickFreq
	{
		TickFreq_1HZ = 1000,
		TickFreq_10HZ = 100,
		TickFreq_100HZ = 10,
		TickFreq_1KHZ = 1,
		TickFreq_DEFAULT = TickFreq_1KHZ,
	};

	class SystemTimer
	{
	public:
		SystemTimer(const TickFreq freq) :m_freq(freq), m_ticks()
		{
			
		}

		virtual void Init(const uint32_t sysFreq) = 0;

		virtual void Start() = 0;

		virtual void Stop() = 0;

		virtual void OnTick()
		{
			m_ticks += m_freq;
		}

		uint32_t GetTicks() const
		{
			return m_ticks;
		}

	protected:
		const TickFreq m_freq;
		uint32_t m_ticks;
	};
}
