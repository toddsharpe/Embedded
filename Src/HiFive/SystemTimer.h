#pragma once

#include "Assert.h"
#include "Sys/SystemTimer.h"

#include <cstdint>
#include <FE310.h>
#include <RiscV.h>

namespace HiFive
{
	class SystemTimer : public Sys::SystemTimer
	{
	public:
		SystemTimer(const Sys::TickFreq freq);

		virtual void Init(const uint32_t sysFreq) override;

		virtual void Start() override;
		virtual void Stop() override;

		virtual void OnTick() override;
	};
}
