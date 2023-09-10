// MAN: Docs\SiFive\fe310-g002-v1p5.pdf

#include "SoC/Uart.h"

namespace SoC
{
	Uart::Uart(uart_block *uart) :
		DgramChannel(),
		m_uart(uart)
	{

	}

	void Uart::Init()
	{

	}

	void Uart::Write(const std::string &string)
	{
		const ReadOnlyBuffer buffer = { string.c_str(), string.length() };
		this->Write(buffer);
	}

	void Uart::Write(const ReadOnlyBuffer& buffer)
	{
		const uint8_t* data = (uint8_t*)buffer.Data;
		for (size_t i = 0; i < buffer.Length; i++)
		{
			while (m_uart->txdata.full) {};
			m_uart->txdata.data = data[i];
		}
		while (m_uart->txdata.full) {};
	}

	ReadOnlyBuffer Uart::Read()
	{
		return ReadOnlyBuffer();
	}
}
