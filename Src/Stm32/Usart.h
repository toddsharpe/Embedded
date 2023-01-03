#pragma once

#include "StringPrinter.h"
#include <cstdint>
#include <cstring>
#include <string>
#include "stm32f7xx.h"
#include "Callback.h"
#include "Assert.h"
#include "RingBuffer.h"
#include "DataChannel.h"

#define UART_DIV_SAMPLING16(__PCLK__, __BAUD__) (((__PCLK__) + ((__BAUD__) / 2U)) / (__BAUD__))

struct UartConfig
{
	uint32_t BaudRate;
};

static constexpr UartConfig const UartDefault = { .BaudRate = 115200 };

class Usart: public DataChannel, public StringPrinter
{
public:
	static void OnInterrupt(void* arg) { ((Usart*)arg)->OnInterrupt(); };

	Usart(USART_TypeDef *usart) : DataChannel(), m_usart(usart), m_buffer()
	{
		
	}

	void Init(const uint32_t clkFreq, const UartConfig& config)
	{
		m_usart->CR1 &= ~USART_CR1_UE; // turn it off
		m_usart->BRR = (uint32_t)(UART_DIV_SAMPLING16(clkFreq, config.BaudRate));
		m_usart->CR1 |= (USART_CR1_RE | USART_CR1_TE); // Enable RX, TX

		CLEAR_BIT(m_usart->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
		CLEAR_BIT(m_usart->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));

		NVIC_EnableIRQ(GetInterupt());

		m_usart->CR1 |= USART_CR1_UE; // USART Enable.
	}

	void EnableInterrupt(const uint32_t interrupt)
	{
		SET_BIT(m_usart->CR1, interrupt);
	}

	void Write(const uint8_t* buffer, size_t length)
	{
		for (size_t i = 0; i < length; i++)
		{
			while (!(m_usart->ISR & USART_ISR_TXE)) { };
			m_usart->TDR = buffer[i];
		}
		while (!(m_usart->ISR & USART_ISR_TC)) {};
	}

	virtual void Write(const std::string& string) override
	{
		this->Write((const uint8_t*)string.c_str(), (int)string.length());
	}

	void Read(uint8_t* buffer, size_t length)
	{
		AssertOp(length, <=, m_buffer.Count());
		Assert(buffer != nullptr);

		for (size_t i = 0; i < length; i++)
		{
			!m_buffer.Read(*buffer);
			buffer++;
		}
	}

	size_t BytesAvailable()
	{
		return m_buffer.Count();
	}

	void OnInterrupt()
	{
		if (m_usart->ISR & USART_ISR_RXNE)
		{
			const uint8_t b = (uint8_t)m_usart->RDR;
			m_buffer.Write(b);
		}
		else if (m_usart->ISR & USART_ISR_IDLE)
		{
			SET_BIT(m_usart->ICR, USART_ICR_IDLECF);
			if (DataReceived.IsCallable() && (m_buffer.Count() > 0))
				DataReceived.Invoke(m_buffer.Count());
		}
	}

	IRQn_Type GetInterupt()
	{
		if (m_usart == USART2)
			return IRQn_Type::USART2_IRQn;
		else if (m_usart == USART3)
			return IRQn_Type::USART3_IRQn;
		else
			return (IRQn_Type)255;
	}

private:
	static constexpr size_t BUFFER_SIZE = 1024;

	USART_TypeDef *m_usart;
	RingBuffer<uint8_t, BUFFER_SIZE> m_buffer;
};