#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>

enum class WaitStatus
{
	None,
	Signaled,
	Timeout,
};

enum class ThreadPriority
{
	Unset,
	Low,
	Normal,
	High,
};
typedef void (*ThreadStart)();

typedef uint32_t milli_t;//Time in milliseconds

struct KernelStats
{
	uint32_t Threads;
	uint32_t SysTicks;
};
