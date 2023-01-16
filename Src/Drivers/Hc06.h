#pragma once

#include <map>
#include <cstdint>
#include "Assert.h"
#include "stm32/Usart.h"
#include "Event.h"
#include "DataChannel.h"

class Hc06: public DataChannel
{
public:
	static void OnDataReceived(void* arg, const size_t bytesAvailable) { ((Hc06*)arg)->OnDataReceived(bytesAvailable); };

	Hc06(Usart& uart) : DataChannel(), m_uart(uart), m_event(), m_internalOp()
	{

	}

	void Init()
	{
		//Ensure RX and Idle is enabled
		m_uart.EnableInterrupt(USART_CR1_RXNEIE | USART_CR1_IDLEIE);
		
		m_uart.DataReceived.Context = this;
		m_uart.DataReceived.Handler = &Hc06::OnDataReceived;

		//VerifyCommand("AT", "OK");
	}

	void VerifyCommand(const std::string& request, const std::string& response)
	{
		m_internalOp = true;
		m_uart.Write(request);

		m_event.WaitFor();

		uint8_t buffer[32] = {};
		m_uart.Read(buffer, m_uart.BytesAvailable());
		Assert(std::string((char*)&buffer[0]) == response);
	}

	void OnDataReceived(const size_t bytesAvailable)
	{
		if (m_internalOp)
		{
			m_internalOp = false;
			m_event.Set();
		}
		else
		{
			if (DataReceived.IsCallable())
				DataReceived.Invoke(m_uart.BytesAvailable());
		}
	}

	virtual void Write(const uint8_t* buffer, size_t length) override
	{
		m_uart.Write(buffer, length);
	}

	virtual void Read(uint8_t* buffer, size_t length) override
	{
		m_uart.Read(buffer, length);
	}

	virtual size_t BytesAvailable() override
	{
		return m_uart.BytesAvailable();
	}

private:
/*
	static constexpr std::map<uint32_t, char> BAUD_RATES = 
	{
		{ 1200, '1' }, { 2400, '2' }, { 4800, '3' }, { 9600, '4' },
		{ 19200, '5' }, { 38400, '6' }, { 57600, '7' }, { 115200, '8' },
		{ 230400, '9' }, { 460800, 'A' }, { 921600, 'B' }, { 1382400, 'C' },
	};*/

	Usart& m_uart;
	Event m_event;
	bool m_internalOp;
};