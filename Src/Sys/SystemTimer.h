#pragma once

#include <cstdint>

namespace SystemTimer
{
	enum TickFreq
	{
		TickFreq_1HZ = 1000,
		TickFreq_10HZ = 100,
		TickFreq_100HZ = 10,
		TickFreq_1KHZ = 1,
		TickFreq_DEFAULT = TickFreq_1KHZ,
	};
	
	void Init(const uint32_t sysFreq, const TickFreq tickFreq);

	void Start();
	void Stop();

	void OnTick();
	uint32_t GetTicks();
}
