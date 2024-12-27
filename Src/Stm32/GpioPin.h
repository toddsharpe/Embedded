// STM: stm32f746ng.pdf

#pragma once

#include <stddef.h>
#include <cstdint>
#if defined(STM32F746xx)
	#include <stm32f746xx.h>
#else
	#include "stm32f401xc.h"
#endif

namespace Stm32
{
	namespace
	{
		//NOTE(tsharpe): Beware both mask and value are shifted by offset, making this difficult to really use with CMSIS
		#define SET_REG_FIELD(reg, offset, mask, value)\
		do\
		{\
			uint32_t temp;\
			temp = reg;\
			temp &= ~((mask) << (offset));\
			temp |= ((value) << (offset));\
			reg = temp;\
		} while (false)
	}
	
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
		Tim4 = 2,
		Spi1 = 5,
		Ltdc9 = 9,
		Eth = 11,
		Ltdc14 = 14,
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
	static constexpr GpioPinConfig const GpioLtdc9 = {.Mode = GpioMode::Alternate, .OutputType = GpioOutputType::PushPull, .PullType = GpioPullType::None, .Speed = GpioSpeed::Low, .Alternate = GpioAlternate::Ltdc9};
	static constexpr GpioPinConfig const GpioEth = {.Mode = GpioMode::Alternate, .OutputType = GpioOutputType::PushPull, .PullType = GpioPullType::None, .Speed = GpioSpeed::VeryHigh, .Alternate = GpioAlternate::Eth};
	static constexpr GpioPinConfig const GpioLtdc14 = {.Mode = GpioMode::Alternate, .OutputType = GpioOutputType::PushPull, .PullType = GpioPullType::None, .Speed = GpioSpeed::Low, .Alternate = GpioAlternate::Ltdc14};

	class GpioPin
	{
	public:
		static void Configure(GPIO_TypeDef * const gpio, const size_t pin, const GpioPinConfig &config, const bool initValue = false)
		{
			GpioPin gpioPin(gpio, pin);
			gpioPin.Init(config, initValue);
		}

		GpioPin(GPIO_TypeDef *const gpio, const size_t pin) :
			m_gpio(gpio),
			m_pin(pin)
		{}

		void Init(const GpioPinConfig &config, const bool initValue = false)
		{
			Set(initValue);

			if (config.Mode == GpioMode::Output || config.Mode == GpioMode::Alternate)
			{
				SET_REG_FIELD(m_gpio->OSPEEDR, m_pin * 2, GpioSpeed::GpioSpeedMask, config.Speed);
				SET_REG_FIELD(m_gpio->OTYPER, m_pin, GpioOutputType::GpioOutputTypeMask, config.OutputType);
			}

			if (config.Mode != GpioMode::Analog)
			{
				SET_REG_FIELD(m_gpio->PUPDR, m_pin * 2, GpioPullType::GpioPullTypeMask, config.PullType);
			}

			if (config.Mode == GpioMode::Alternate)
			{
				SET_REG_FIELD(m_gpio->AFR[m_pin >> 3], (m_pin & 0b111) * 4, GpioAlternate::GpioAlternateMask, config.Alternate);
			}

			SET_REG_FIELD(m_gpio->MODER, m_pin * 2, GpioMode::GpioModeMask, config.Mode);
		}

		void Set(const bool value)
		{
			m_gpio->BSRR = (1 << (m_pin + (value ? 0 : 16)));
		}

		bool Get()
		{
			return (m_gpio->ODR & (1 << m_pin)) != 0;
		}

		void Toggle()
		{
			Set(!Get());
		}

		bool Read()
		{
			return (m_gpio->IDR & (1 << m_pin)) != 0;
		}

	private:
		GPIO_TypeDef *m_gpio;
		const size_t m_pin;
	};
}
