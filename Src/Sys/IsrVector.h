#pragma once

#include <cstdint>

namespace IsrVector
{
	typedef void (*InterruptHandler)(void* arg);
	struct InterruptContext
	{
		InterruptHandler Handler;
		void* Context;
	};

	bool Handle(const uint8_t interrupt);
	void Register(const uint8_t interrupt, const InterruptContext &context);
	void Unregister(const uint8_t interrupt);
}
