#pragma once

#include <map>
#include <cstdint>
#include "Assert.h"
#include "Stm32/Usart.h"
#include "Event.h"
#include "DgramChannel.h"

class Hc06: public DgramChannel
{
public:
	static void OnDgramReceived(void* arg) { ((Hc06*)arg)->OnDgramReceived(); };

	Hc06(Stm32::Usart& uart) :
		DgramChannel(),
		m_uart(uart),
		m_event(),
		m_internalOp()
	{

	}

	void Init()
	{
		//Ensure RX and Idle is enabled
		m_uart.EnableInterrupt(USART_CR1_RXNEIE | USART_CR1_IDLEIE);
		
		m_uart.DgramReceived.Context = this;
		m_uart.DgramReceived.Handler = &Hc06::OnDgramReceived;

		//VerifyCommand("AT", "OK");
	}

	void VerifyCommand(const std::string& request, const std::string& response)
	{
		m_internalOp = true;
		m_uart.Write(request);

		//Blocks and waits
		m_event.WaitFor();

		//Verify response
		const ReadOnlyBuffer dgram = m_uart.Read();
		Assert(std::string((char*)dgram.Length) == response);
	}

	void OnDgramReceived()
	{
		if (m_internalOp)
		{
			m_internalOp = false;
			m_event.Set();
		}
		else
		{
			if (DgramReceived.IsCallable())
				DgramReceived.Invoke();
		}
	}

	virtual void Write(const ReadOnlyBuffer& buffer) override
	{
		m_uart.Write(buffer);
	}

	virtual ReadOnlyBuffer Read() override
	{
		return m_uart.Read();
	}

private:
/*
	static constexpr std::map<uint32_t, char> BAUD_RATES = 
	{
		{ 1200, '1' }, { 2400, '2' }, { 4800, '3' }, { 9600, '4' },
		{ 19200, '5' }, { 38400, '6' }, { 57600, '7' }, { 115200, '8' },
		{ 230400, '9' }, { 460800, 'A' }, { 921600, 'B' }, { 1382400, 'C' },
	};*/

	Stm32::Usart& m_uart;
	Event m_event;
	bool m_internalOp;
};
