#pragma once

#include "StringPrinter.h"
#include "Rtos/Types.h"
#include "stm32f7xx.h"
#include "Callback.h"
#include "Assert.h"
#include "RingBuffer.h"
#include "DgramChannel.h"

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

	//Uart bytes are read into ringbuffer, which is copied to staging buffer on idle
	//TODO(tsharpe): Remove RingBuffer and go right into static buffer?
	class Usart: public DgramChannel
	{
	public:
		static void OnInterrupt(void* arg) { ((Usart*)arg)->OnInterrupt(); };

		Usart(USART_TypeDef *usart) :
			DgramChannel(),
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

		void EnableInterrupt(const uint32_t interrupt)
		{
			SET_BIT(m_usart->CR1, interrupt);
		}

		void Write(const std::string& string)
		{
			const ReadOnlyBuffer buffer = { string.c_str(), string.length() };
			this->Write(buffer);
		}
		
		virtual void Write(const ReadOnlyBuffer& buffer) override
		{
			const uint8_t* data = (uint8_t*)buffer.Data;
			for (size_t i = 0; i < buffer.Length; i++)
			{
				while (!(m_usart->ISR & USART_ISR_TXE)) { };
				m_usart->TDR = data[i];
			}
			while (!(m_usart->ISR & USART_ISR_TC)) {};
		}

		virtual ReadOnlyBuffer Read() override
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

	private:
		static constexpr size_t BUFFER_SIZE = 1024;

		void OnInterrupt()
		{
			Write("OnInterrupt\r\n");
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
