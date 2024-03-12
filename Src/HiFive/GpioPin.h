// MAN: fe310-g002-manual-v19p05.pdf

#pragma once

#include "Assert.h"

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

	class GpioPin
	{
	public:
		GpioPin(const size_t pin) :
			m_pin(pin)
		{}

		void Init(const GpioPinConfig &config, const bool initValue = false)
		{
			if (config.Mode == GpioMode::Output)
			{
				Set(initValue);

				GPIO0->input_en &= ~(1 << m_pin);
				GPIO0->output_en |= (1 << m_pin);
			}
			else
			{
				GPIO0->input_en |= (1 << m_pin);
				GPIO0->output_en &= ~(1 << m_pin);
			}

			// TODO(tsharpe): Why is this required or else output has to be inverted?
			GPIO0->out_xor |= (1 << m_pin);
		}

		void Set(const bool value)
		{
			if (value)
				GPIO0->output_val |= (1 << m_pin);
			else
				GPIO0->output_val &= ~(1 << m_pin);
		}

		bool Get()
		{
			return (GPIO0->output_val) != 0;
		}

		bool Read()
		{
			return (GPIO0->input_val & (1 << m_pin)) != 0;
		}
	private:
		const size_t m_pin;
	};
}
