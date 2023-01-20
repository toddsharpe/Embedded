// STM: stm32f746ng.pdf

#pragma once

#include "Util.h"
#include "Sys/GpioPin.h"

#include <stddef.h>
#include <cstdint>
#include <stm32f746xx.h>

namespace Stm32
{
	enum GpioMode : uint8_t
	{
		Input = 0b00,
		Output = 0b01,
		Alternate = 0b10,
		Analog = 0b11,
		GpioModeMask = 0b11
	};

	enum GpioOutputType : uint8_t
	{
		PushPull = 0b0,
		OpenDrain = 0b1,
		GpioOutputTypeMask = 0b1
	};

	enum GpioPullType
	{
		None = 0b00,
		PullUp = 0b01,
		PullDown = 0b10,
		Reserved = 0b11,
		GpioPullTypeMask = 0b11
	};

	enum GpioSpeed
	{
		Low = 0b00,
		Medium = 0b01,
		High = 0b10,
		VeryHigh = 0b11,
		GpioSpeedMask = High
	};

	// STM: Table 12 Alternate function mapping
	enum GpioAlternate
	{
		Usart1 = 7,
		Usart2 = 7,
		Usart3 = 7,
		Spi1 = 5,
		GpioAlternateMask = 0b1111
	};

	struct GpioPinConfig
	{
		GpioMode Mode;
		GpioOutputType OutputType;
		GpioPullType PullType;
		GpioSpeed Speed;
		GpioAlternate Alternate;
	};

	static constexpr GpioPinConfig const GpioOutput = {.Mode = GpioMode::Output, .PullType = GpioPullType::None};
	static constexpr GpioPinConfig const GpioInput = {.Mode = GpioMode::Input, .PullType = GpioPullType::None};

	static constexpr GpioPinConfig const GpioUart1 = {.Mode = GpioMode::Alternate, .OutputType = GpioOutputType::PushPull, .PullType = GpioPullType::None, .Speed = GpioSpeed::VeryHigh, .Alternate = GpioAlternate::Usart1};
	static constexpr GpioPinConfig const GpioUart2 = {.Mode = GpioMode::Alternate, .OutputType = GpioOutputType::PushPull, .PullType = GpioPullType::None, .Speed = GpioSpeed::VeryHigh, .Alternate = GpioAlternate::Usart2};
	static constexpr GpioPinConfig const GpioUart3 = {.Mode = GpioMode::Alternate, .OutputType = GpioOutputType::PushPull, .PullType = GpioPullType::None, .Speed = GpioSpeed::VeryHigh, .Alternate = GpioAlternate::Usart3};

	static constexpr GpioPinConfig const GpioSpi1 = {.Mode = GpioMode::Alternate, .OutputType = GpioOutputType::PushPull, .PullType = GpioPullType::None, .Speed = GpioSpeed::VeryHigh, .Alternate = GpioAlternate::Spi1};

	constexpr GPIO_TypeDef *Port_A()
	{
		return GPIOA;
	}

	constexpr GPIO_TypeDef *Port_B()
	{
		return GPIOB;
	}

	constexpr GPIO_TypeDef *Port_C()
	{
		return GPIOC;
	}

	constexpr GPIO_TypeDef *Port_D()
	{
		return GPIOD;
	}

	constexpr GPIO_TypeDef *Port_E()
	{
		return GPIOE;
	}

	constexpr GPIO_TypeDef *Port_F()
	{
		return GPIOF;
	}

	constexpr GPIO_TypeDef *Port_G()
	{
		return GPIOG;
	}

	template <GPIO_TypeDef *PORT(), size_t TPin>
	class GpioPin : public Sys::GpioPin
	{
	public:
		GpioPin()
		{
		}

		void Init(const GpioPinConfig &config, const bool initValue = false)
		{
			Set(initValue);

			if (config.Mode == GpioMode::Output || config.Mode == GpioMode::Alternate)
			{
				SET_REG_FIELD(PORT()->OSPEEDR, TPin * 2, GpioSpeed::GpioSpeedMask, config.Speed);
				SET_REG_FIELD(PORT()->OTYPER, TPin, GpioOutputType::GpioOutputTypeMask, config.OutputType);
			}

			if (config.Mode != GpioMode::Analog)
			{
				SET_REG_FIELD(PORT()->PUPDR, TPin * 2, GpioPullType::GpioPullTypeMask, config.PullType);
			}

			if (config.Mode == GpioMode::Alternate)
			{
				SET_REG_FIELD(PORT()->AFR[TPin >> 3], (TPin & 0b111) * 4, GpioAlternate::GpioAlternateMask, config.Alternate);
			}

			SET_REG_FIELD(PORT()->MODER, TPin * 2, GpioMode::GpioModeMask, config.Mode);
		}

		virtual void Set(const bool value) override
		{
			PORT()->BSRR = (1 << (TPin + (value ? 0 : 16)));
		}

		virtual bool Get() override
		{
			return (PORT()->ODR & (1 << TPin)) != 0;
		}

		virtual bool Read() override
		{
			return (PORT()->IDR & (1 << TPin)) != 0;
		}
	};
}
