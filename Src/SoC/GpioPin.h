#pragma once

#include "Assert.h"

#include <SoC.h>

namespace SoC
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
	static constexpr GpioPinConfig const GpioInput = {.Mode = GpioMode::Input};
	
	class GpioPin
	{
	public:
		GpioPin(gpio_block* const gpio, const size_t pin) :
			m_gpio(gpio),
			m_pin(pin)
		{

		}

		void Init(const GpioPinConfig &config, const bool initValue = false)
		{
			if (config.Mode == GpioMode::Output)
			{
				Set(initValue);
				
				m_gpio->dir |= (1 << m_pin);
			}
			else
			{
				m_gpio->dir &= ~(1 << m_pin);
			}
		}

		void Set(const bool value)
		{
			if (value)
				m_gpio->data_out |= (1 << m_pin);
			else
				m_gpio->data_out &= ~(1 << m_pin);
		}

		bool Get()
		{
			return (m_gpio->data_out) != 0;
		}

		bool Read()
		{
			return (m_gpio->data_in & (1 << m_pin)) != 0;
		}

	private:
		gpio_block* const m_gpio;
		const size_t m_pin;
	};
}
