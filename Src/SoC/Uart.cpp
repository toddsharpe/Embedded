// MAN: Docs\SiFive\fe310-g002-v1p5.pdf

#include "SoC/Uart.h"

namespace SoC
{
	Uart::Uart(uart_block *uart) : DataChannel(), m_uart(uart)
	{

	}

	void Uart::Init()
	{

	}

	void Uart::Write(const std::string &string)
	{
		this->Write((const uint8_t *)string.c_str(), (int)string.length());
	}

	void Uart::Write(const uint8_t *buffer, size_t length)
	{
		for (size_t i = 0; i < length; i++)
		{
			while (m_uart->txdata.full) {};
			m_uart->txdata.data = buffer[i];
		}
		while (m_uart->txdata.full) {};
	}

	void Uart::Read(uint8_t *buffer, size_t length)
	{

	}

	size_t Uart::BytesAvailable()
	{
		return 0;
	}
}
