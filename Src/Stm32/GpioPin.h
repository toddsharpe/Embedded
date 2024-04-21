// STM: stm32f746ng.pdf

#pragma once

#include "Sys/IsrVector.h"
#include "Callback.h"
#include <stddef.h>
#include <cstdint>
#include <stm32f7xx.h>
#include <stm32f746xx.h>

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

		size_t GetIndex(const GPIO_TypeDef * const gpio)
		{
			const uintptr_t base = (uintptr_t)GPIOA;
			const uintptr_t size = (uintptr_t)GPIOB - base;
			const uintptr_t offset = (uintptr_t)gpio - base;
			return offset / size;
		}
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
		static void OnInterupt(void* arg) { ((GpioPin*)arg)->OnInterupt(); };

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

		//NOTE(tsharpe): Method only does rising edge.
		void EnableInterrupt()
		{
			//Enable syscfg
			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
			__DSB();

			//Set interrupt configuration
			const size_t i = m_pin >> 2;
			const size_t offset = m_pin & 0x03;
			const size_t gpioIndex = GetIndex(m_gpio);
			SET_REG_FIELD(SYSCFG->EXTICR[i], 4 * offset, 0xF, gpioIndex);

			//Set interrupt mask
			const uint32_t mask = (1 << m_pin);
			SET_BIT(EXTI->IMR, mask);

			//Clear event mask
			CLEAR_BIT(EXTI->EMR, mask);

			//Set rising edge
			SET_BIT(EXTI->RTSR, mask);

			//Clear falling edge
			CLEAR_BIT(EXTI->FTSR, mask);

			//Enable interrupts
			NVIC_EnableIRQ(GetInterupt());
		}

		void OnInterupt()
		{
			//Signal
			if (Interrupt.IsCallable())
				Interrupt.Invoke();
		}

		void Set(const bool value)
		{
			m_gpio->BSRR = (1 << (m_pin + (value ? 0 : 16)));
		}

		bool Get()
		{
			return (m_gpio->ODR & (1 << m_pin)) != 0;
		}

		bool Read()
		{
			return (m_gpio->IDR & (1 << m_pin)) != 0;
		}

		IRQn_Type GetInterupt()
		{
			if (m_pin < 5)
				return (IRQn_Type)(EXTI0_IRQn + m_pin);
			else if (m_pin < 10)
				return EXTI9_5_IRQn;
			else
				return EXTI15_10_IRQn;
		}

		Callback Interrupt;

	private:
		GPIO_TypeDef *m_gpio;
		const size_t m_pin;
	};
}
