// MAN: Docs\SiFive\fe310-g002-v1p5.pdf

#include "HiFive/Uart.h"

namespace HiFive
{
	void Uart::OnInterrupt(void* arg) { ((Uart*)arg)->OnInterrupt(); };

	Uart::Uart(UART0_Type *uart) : DataChannel(), m_uart(uart), m_buffer()
	{

	}

	void Uart::Init(const uint32_t clkFreq, const UartConfig& config)
	{
		m_uart->txctrl_b.enable = 0;
		m_uart->rxctrl_b.enable = 0;

		m_uart->div = clkFreq / config.BaudRate - 1;
		m_uart->txctrl_b.enable = true;
		m_uart->rxctrl_b.enable = true;
	}

	void Uart::Write(const std::string &string)
	{
		this->Write((const uint8_t *)string.c_str(), (int)string.length());
	}

	void Uart::Write(const uint8_t *buffer, size_t length)
	{
		for (size_t i = 0; i < length; i++)
		{
			while (m_uart->txdata_b.full) {};
			m_uart->txdata_b.data = buffer[i];
		}
		while (m_uart->txdata_b.full) {};
	}

	void Uart::Read(uint8_t *buffer, size_t length)
	{

	}

	size_t Uart::BytesAvailable()
	{
		return 0;
	}

	void Uart::EnableInterrupt()
	{
		m_uart->ie_b.rxwm = true;
	}

	void Uart::OnInterrupt()
	{
		if (m_uart->ip_b.rxwm)
		{
			const uint8_t b = (uint8_t)m_uart->rxdata_b.data;
			m_buffer.Write(b);

			if (DataReceived.IsCallable() && (m_buffer.Count() > 0))
				DataReceived.Invoke(m_buffer.Count());
		}
	}
}
