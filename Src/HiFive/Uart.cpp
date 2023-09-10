// MAN: Docs\SiFive\fe310-g002-v1p5.pdf

#include "HiFive/Uart.h"

namespace HiFive
{
	void Uart::OnInterrupt(void* arg) { ((Uart*)arg)->OnInterrupt(); };

	Uart::Uart(UART0_Type *uart) :
		DgramChannel(),
		m_uart(uart),
		m_buffer()
	{

	}

	void Uart::Init(const uint32_t clkFreq, const UartConfig& config)
	{
		m_uart->txctrl_b.enable = 0;
		m_uart->rxctrl_b.enable = 0;

		m_uart->div = clkFreq / config.BaudRate - 1;
		m_uart->txctrl_b.enable = true;
		m_uart->rxctrl_b.enable = true;

		//Enable RX Interrupt
		m_uart->ie_b.rxwm = true;
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
			while (m_uart->txdata_b.full) {};
			m_uart->txdata_b.data = data[i];
		}
		while (m_uart->txdata_b.full) {};
	}

	ReadOnlyBuffer Uart::Read()
	{
		return ReadOnlyBuffer();
	}

	void Uart::OnInterrupt()
	{
		if (m_uart->ip_b.rxwm)
		{
			const uint8_t b = (uint8_t)m_uart->rxdata_b.data;
			m_buffer.Write(b);

			//TODO(tsharpe): Idle check and invoke dgram
		}
	}
}
