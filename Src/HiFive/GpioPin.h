// MAN: fe310-g002-manual-v19p05.pdf

#pragma once

#include "Assert.h"
#include "Sys/GpioPin.h"

#include <FE310.h>
#include <stddef.h>
#include <cstdint>

namespace HiFive
{
	enum GpioMode : uint8_t
	{
		Input = 0b0,
		Output = 0b1,
	};

	struct GpioPinConfig
	{
		GpioMode Mode;
	};

	static constexpr GpioPinConfig const GpioOutput = {.Mode = GpioMode::Output};

	template <size_t TPin>
	class GpioPin : public Sys::GpioPin
	{
	public:
		GpioPin()
		{
		}

		void Init(const GpioPinConfig &config, const bool initValue = false)
		{
			Set(initValue);

			if (config.Mode == GpioMode::Output)
			{
				GPIO0->input_en &= ~(1 << TPin);
				GPIO0->output_en |= (1 << TPin);
			}
			else
			{
				GPIO0->input_en |= (1 << TPin);
				GPIO0->output_en &= ~(1 << TPin);
			}

			// TODO(tsharpe): Why is this required or else output has to be inverted?
			GPIO0->out_xor |= (1 << TPin);
		}

		virtual void Set(const bool value) override
		{
			if (value)
				GPIO0->output_val |= (1 << TPin);
			else
				GPIO0->output_val &= ~(1 << TPin);
		}

		virtual bool Get() override
		{
			return (GPIO0->output_val) != 0;
		}

		virtual bool Read() override
		{
			return (GPIO0->input_val & (1 << TPin)) != 0;
		}
	};
}
