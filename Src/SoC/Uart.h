// MAN: Docs\SiFive\fe310-g002-v1p5.pdf

#pragma once

#include "Assert.h"
#include "Buffer.h"

#include <cstdint>
#include <SoC.h>
#include <string>

namespace SoC
{
	class Uart
	{
	public:
		Uart(uart_block *const uart) :
			m_uart(uart)
		{}

		void Init()
		{

		}

		void Write(const std::string &string)
		{
			const ReadOnlyBuffer buffer = { string.c_str(), string.length() };
			this->Write(buffer);
		}

		void Write(const ReadOnlyBuffer& buffer)
		{
			const uint8_t* data = (uint8_t*)buffer.Data;
			for (size_t i = 0; i < buffer.Length; i++)
			{
				while (m_uart->txdata.full) {};
				m_uart->txdata.data = data[i];
			}
			while (m_uart->txdata.full) {};
		}

		ReadOnlyBuffer Read()
		{
			return ReadOnlyBuffer();
		}

	private:
		uart_block *const m_uart;
	};
}
