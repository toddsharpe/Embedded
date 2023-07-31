#pragma once

#include <cstdint>
#include <cstddef>

struct ReadOnlyBuffer
{
	const void* Data;
	size_t Length;
};

struct Buffer
{
	void* Data;
	size_t Length;
};

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

typedef void (*InterruptHandler)(void* arg);
struct InterruptContext
{
	InterruptHandler Handler;
	void* Context;
};

typedef uint32_t milli_t;//Time in milliseconds

struct KernelStats
{
	uint32_t Threads;
	uint32_t SysTicks;
};
typedef uint8_t InterruptVector;
