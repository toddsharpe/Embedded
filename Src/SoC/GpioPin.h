#pragma once

#include "Assert.h"
#include "Sys/GpioPin.h"

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
	
	template <size_t TPin>
	class GpioPin : public Sys::GpioPin
	{
	public:
		static void Configure(const GpioPinConfig &config, const bool initValue = false)
		{
			GpioPin<TPin> pin;
			pin.Init(config, initValue);
		}

		GpioPin() : Sys::GpioPin(), m_gpio(GPIO1)
		{

		}

		void Init(const GpioPinConfig &config, const bool initValue = false)
		{
			if (config.Mode == GpioMode::Output)
			{
				Set(initValue);
				
				m_gpio->dir |= (1 << TPin);
			}
			else
			{
				m_gpio->dir &= ~(1 << TPin);
			}
		}

		virtual void Set(const bool value) override
		{
			if (value)
				m_gpio->data_out |= (1 << TPin);
			else
				m_gpio->data_out &= ~(1 << TPin);
		}

		virtual bool Get() override
		{
			return (m_gpio->data_out) != 0;
		}

		virtual bool Read() override
		{
			return (m_gpio->data_in & (1 << TPin)) != 0;
		}

	private:
		gpio_block* const m_gpio;
	};
}