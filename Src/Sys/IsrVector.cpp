#include "Assert.h"
#include "Arm.h"
#include "Board.h"
#include "Sys/IsrVector.h"

#include <map>
#include <limits>
#include <cstdint>

namespace
{
	std::map<uint8_t, IsrVector::InterruptContext> m_interruptHandlers;
}

namespace IsrVector
{
	bool Handle(const uint8_t interrupt)
	{
		const auto &it = m_interruptHandlers.find(interrupt);
		if (it == m_interruptHandlers.end())
			return false;

		IsrVector::InterruptContext ctx = it->second;
		ctx.Handler(ctx.Context);
		return true;
	}

	void Register(const uint8_t interrupt, const InterruptContext &context)
	{
		Assert(m_interruptHandlers.find(interrupt) == m_interruptHandlers.end());
		m_interruptHandlers.insert({interrupt, context});
	}

	void Unregister(const uint8_t interrupt)
	{
		Assert(m_interruptHandlers.find(interrupt) != m_interruptHandlers.end());
		m_interruptHandlers.erase(interrupt);
	}
}
