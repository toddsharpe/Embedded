#pragma once

#include "Buffer.h"
#include "stm32f7xx.h"
#include "Callback.h"
#include "Assert.h"
#include "RingBuffer.h"

#include <cstdint>
#include <cstring>
#include <string>

#define UART_DIV_SAMPLING16(__PCLK__, __BAUD__) (((__PCLK__) + ((__BAUD__) / 2U)) / (__BAUD__))

namespace Stm32
{
	struct UartConfig
	{
		uint32_t BaudRate;
	};

	static constexpr UartConfig const UartDefault = { .BaudRate = 115200 };

	class Usart
	{
	public:
		static void OnInterupt(void* arg) { ((Usart*)arg)->OnInterupt(); };

		Usart(USART_TypeDef *usart) :
			m_usart(usart),
			m_ringBuffer(),
			m_buffer()
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

		void EnableRx()
		{
			SET_BIT(m_usart->CR1, USART_CR1_RXNEIE | USART_CR1_IDLEIE);
		}

		void Write(const std::string& string)
		{
			const ReadOnlyBuffer buffer = { string.c_str(), string.length() };
			this->Write(buffer);
		}

		void Write(const ReadOnlyBuffer& buffer)
		{
			const uint8_t* data = (uint8_t*)buffer.Data;
			for (size_t i = 0; i < buffer.Length; i++)
			{
				while (!(m_usart->ISR & USART_ISR_TXE)) { };
				m_usart->TDR = data[i];
			}
			while (!(m_usart->ISR & USART_ISR_TC)) {};
		}

		ReadOnlyBuffer Read()
		{
			return { m_buffer.Data, m_buffer.Length };
		}

		IRQn_Type GetInterupt()
		{
			if (m_usart == USART1)
				return IRQn_Type::USART1_IRQn;
			if (m_usart == USART2)
				return IRQn_Type::USART2_IRQn;
			else if (m_usart == USART3)
				return IRQn_Type::USART3_IRQn;
			else
				return (IRQn_Type)255;
		}

		Callback DgramReceived;

	private:
		static constexpr size_t BUFFER_SIZE = 1024;

		void OnInterupt()
		{
			if (m_usart->ISR & USART_ISR_RXNE)
			{
				const uint8_t b = (uint8_t)m_usart->RDR;
				m_ringBuffer.Write(b);
			}
			else if (m_usart->ISR & USART_ISR_IDLE)
			{
				SET_BIT(m_usart->ICR, USART_ICR_IDLECF);

				if (m_ringBuffer.Count() == 0)
					return;

				Assert(m_ringBuffer.CopyTo(m_buffer));

				//Signal
				if (DgramReceived.IsCallable())
					DgramReceived.Invoke();
			}
		}

		USART_TypeDef *m_usart;
		RingBuffer<uint8_t, BUFFER_SIZE> m_ringBuffer;
		StaticBuffer<BUFFER_SIZE> m_buffer;
	};
}
