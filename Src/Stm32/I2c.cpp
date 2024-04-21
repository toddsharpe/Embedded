#include "Assert.h"
#include "Stm32/I2c.h"

namespace Stm32
{
	namespace
	{
		uint32_t GetRccEnFlag(I2C_TypeDef* const i2c)
		{
			if (i2c == I2C1)
				return RCC_APB1ENR_I2C1EN;
			else if (i2c == I2C2)
				return RCC_APB1ENR_I2C2EN;
			else if (i2c == I2C3)
				return RCC_APB1ENR_I2C3EN;
			else if (i2c == I2C4)
				return RCC_APB1ENR_I2C4EN;

			Assert(false);
		}
	}
	
	I2c::I2c(I2C_TypeDef* const i2c) : 
		m_i2c(i2c)
	{

	}

	void I2c::Init(const I2cConfig config)
	{
		RCC->APB1ENR |= GetRccEnFlag(m_i2c);

		CLEAR_BIT(m_i2c->CR1, I2C_CR1_PE);

		m_i2c->TIMINGR = config.Timing;

		SET_BIT(m_i2c->CR1, I2C_CR1_PE);
	}

	void I2c::Write(const ReadOnlyBuffer& buffer)
	{

	}
}
