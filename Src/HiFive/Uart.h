// MAN: Docs\SiFive\fe310-g002-v1p5.pdf

#pragma once

#include "Assert.h"
#include "RingBuffer.h"

#include <cstdint>
#include <FE310.h>
#include <string>

namespace HiFive
{
	struct UartConfig
	{
		uint32_t BaudRate;
	};

	static constexpr UartConfig const UartDefault = { .BaudRate = 115200 };

	//NOTE(tsharpe): Default values - txctrl: 0x1001, rxctrl: 0x01, div: 0x8A
	class Uart
	{
	public:
		static void OnInterrupt(void* arg) { ((Uart*)arg)->OnInterrupt(); };

		Uart(UART0_Type *uart) :
			m_uart(uart),
			m_buffer()
		{

		}

		void Init(const uint32_t clkFreq, const UartConfig& config)
		{
			m_uart->txctrl_b.enable = 0;
			m_uart->rxctrl_b.enable = 0;

			m_uart->div = clkFreq / config.BaudRate - 1;
			m_uart->txctrl_b.enable = true;
			m_uart->rxctrl_b.enable = true;

			//Enable RX Interrupt
			m_uart->ie_b.rxwm = true;
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
				while (m_uart->txdata_b.full) {};
				m_uart->txdata_b.data = data[i];
			}
			while (m_uart->txdata_b.full) {};
		}

		ReadOnlyBuffer Read()
		{
			return ReadOnlyBuffer();
		}

		void OnInterrupt()
		{
			if (m_uart->ip_b.rxwm)
			{
				const uint8_t b = (uint8_t)m_uart->rxdata_b.data;
				m_buffer.Write(b);

				//TODO(tsharpe): Idle check and invoke dgram
			}
		}

	private:
		static constexpr size_t BUFFER_SIZE = 1024;

		UART0_Type *m_uart;
		RingBuffer<uint8_t, BUFFER_SIZE> m_buffer;
	};
}
