#include "Assert.h"
#include "Board.h"
#include "Stm32/I2c.h"
#include "I2c.h"
#include "Util.h"
#include <algorithm>

//MAN: rm0385

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
			return 0;
		}
	}
	
	I2c::I2c(I2C_TypeDef* const i2c) : 
		m_i2c(i2c)
	{

	}

	void I2c::Init(const I2cConfig config)
	{
		Assert(config.Master);
		Assert(config.Addr7);
		
		RCC->APB1ENR |= GetRccEnFlag(m_i2c);

		//MAN 30.4.8: I2C master mode

		//Disable
		CLEAR_BIT(m_i2c->CR1, I2C_CR1_PE);

		//Timing
		m_i2c->TIMINGR = config.Timing;

		//Enable
		SET_BIT(m_i2c->CR1, I2C_CR1_PE);
	}

	bool I2c::Write(const uint8_t address, const ReadOnlyBuffer& buffer)
	{
		//Master communication initialization
		MODIFY_REG(m_i2c->CR2, I2C_CR2_SADD, (address << 1) & I2C_CR2_SADD);
		CLEAR_BIT(m_i2c->CR2, I2C_CR2_ADD10);
		CLEAR_BIT(m_i2c->CR2, I2C_CR2_RD_WRN);
		SET_BIT(m_i2c->CR2, I2C_CR2_AUTOEND);
		SET_BIT(m_i2c->CR2, I2C_CR2_START);

		while (!READ_BIT(m_i2c->ISR, I2C_ISR_NACKF) && !READ_BIT(m_i2c->ISR, I2C_ISR_STOPF)) {}
		bool success = !READ_BIT(m_i2c->ISR, I2C_ISR_NACKF);

		//Wait for stop bit to be set then clear it
		while (!READ_BIT(m_i2c->ISR, I2C_ISR_STOPF)) {}
		SET_BIT(m_i2c->ICR, I2C_ICR_STOPCF);

		if (READ_BIT(m_i2c->ISR, I2C_ISR_NACKF))
		{
			SET_BIT(m_i2c->ICR, I2C_ICR_NACKCF);
		}
		return success;
	}

	bool I2c::Read(const uint8_t address, const Buffer& buffer)
	{
		const size_t max_chunk = 255;
		
		//Ensure bus isnt busy
		while (READ_BIT(m_i2c->ISR, I2C_ISR_BUSY));

		uint8_t* data = (uint8_t*)buffer.Data;
		size_t count = buffer.Length;
		while (count > 0)
		{
			const size_t chunk = std::clamp(count, size_t(0), max_chunk);
			count -= chunk;
			const uint32_t flag = count == 0 ? I2C_CR2_AUTOEND : I2C_CR2_RELOAD;

			//Set transfer config
			MODIFY_REG(m_i2c->CR2, I2C_CR2_SADD, (address << 1) & I2C_CR2_SADD);
			CLEAR_BIT(m_i2c->CR2, I2C_CR2_ADD10);
			MODIFY_REG(m_i2c->CR2, I2C_CR2_NBYTES, chunk << I2C_CR2_NBYTES_Pos);

			//Set mode by clearing first, then applying
			CLEAR_BIT(m_i2c->CR2, I2C_CR2_RELOAD);
			CLEAR_BIT(m_i2c->CR2, I2C_CR2_AUTOEND);
			SET_BIT(m_i2c->CR2, flag);
			
			//Set read and start
			SET_BIT(m_i2c->CR2, I2C_CR2_RD_WRN);
			SET_BIT(m_i2c->CR2, I2C_CR2_START);

			for (size_t i = 0; i < chunk; i++)
			{
				//Wait for data, asserting no stop conditions
				while (!READ_BIT(m_i2c->ISR, I2C_ISR_RXNE))
				{
					Assert(!READ_BIT(m_i2c->ISR, I2C_ISR_STOPF));
					Assert(!READ_BIT(m_i2c->ISR, I2C_ISR_NACKF));
				}

				*data = (uint8_t)m_i2c->RXDR;
				data++;
			}

			//Wait for TCR
			if (count > 0)
				while (!READ_BIT(m_i2c->ISR, I2C_ISR_TCR));
		}

		//Wait for stop
		while (!READ_BIT(m_i2c->ISR, I2C_ISR_STOPF))
		{
			Assert(!READ_BIT(m_i2c->ISR, I2C_ISR_NACKF));
		}

		//Clear stop
		SET_BIT(m_i2c->ICR, I2C_ICR_STOPCF);

		return true;
	}

	void I2c::Probe()
	{
		Board::Printf("I2c::Probe\r\n");
		
		//Print headers
		const uint32_t width = 16;
		Board::Printf("---- ");
		for (size_t i = 0; i < width; i++)
		{
			Board::Printf("%02x ", (unsigned char)i);
		}
		Board::Printf("\r\n");

		for (uint8_t i = 0; i <= 0x7F; i++)
		{
			if (i != 0 && i % width == 0)
			{
				Board::Printf("\r\n");
			}

			if (i % width == 0)
				Board::Printf("%02x - ", (i / width) << 4);

			//Attempt to write
			bool success = Write(i, {});
			Board::Printf("%s ", success ? "XX" : "--");
		}

		Board::Printf("\r\n");
	}
}

