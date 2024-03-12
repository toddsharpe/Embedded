#pragma once

#include "Callback.h"
#include "Net/IpStack.h"
#include "Buffer.h"
#include <cstdint>


class UdpChannel
{
public:
	static void OnDgramReceived(void* arg, const ReadOnlyBuffer& buffer) { ((UdpChannel*)arg)->OnDgramReceived(buffer); };

	UdpChannel(const Net::IpAddress& serverIp, const uint16_t serverPort) :
		m_serverIp(serverIp),
		m_serverPort(serverPort),
		m_buffer()
	{

	}

	void Init()
	{
		Net::IpStack::DgramReceived = { this, &UdpChannel::OnDgramReceived };
	}

	void Write(const ReadOnlyBuffer& buffer) const
	{
		Net::IpStack::SendUdp(m_serverIp, m_serverPort, buffer);
	}

	ReadOnlyBuffer Read() const
	{
		return { m_buffer.Data, m_buffer.Count };
	}

	Callback DgramReceived;

private:
	void OnDgramReceived(const ReadOnlyBuffer& buffer)
	{
		//Strip IP and UDP header
		const Net::IpHeader* ip = reinterpret_cast<const Net::IpHeader*>(buffer.Data);
		Assert(buffer.Length == Net::ntohs(ip->TotalLength));
		const Net::UdpHeader* udp = reinterpret_cast<const Net::UdpHeader*>(ip + 1);

		//Copy into static buffer
		const ReadOnlyBuffer dgram = { (void*)(udp + 1), Net::ntohs(udp->Length) - sizeof(Net::UdpHeader) };
		Assert(m_buffer.CopyFrom(dgram));

		//Signal
		if (DgramReceived.IsCallable())
			DgramReceived.Invoke();
	}

	const Net::IpAddress& m_serverIp;
	const uint16_t m_serverPort;
	StaticBuffer<EthMac::BufferSize> m_buffer;
};
