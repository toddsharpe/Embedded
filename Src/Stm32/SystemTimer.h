#pragma once

#include "Sys/SystemTimer.h"

#include <cstdint>

namespace Stm32
{
	class SystemTimer : public Sys::SystemTimer
	{
	public:
		SystemTimer(const Sys::TickFreq freq);

		virtual void Init(const uint32_t sysFreq) override;
		virtual void Start() override;
		virtual void Stop() override;
	};
}
