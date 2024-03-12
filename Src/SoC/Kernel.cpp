#include <cstddef>
#include <SoC.h>

namespace Rtos
{
	//NOTE(tsharpe): This uses SocBlock directly, versus a kernel call
	void SleepThread(const size_t ms)
	{
		const uint32_t stop = SOC_BLOCK->cycles + SOC_BLOCK->freq * ms / 1000;
		while (SOC_BLOCK->cycles < stop)
		{
			__asm("nop");
		}
	}
}
