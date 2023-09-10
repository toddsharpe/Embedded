#pragma once

#include "DgramChannel.h"
#include "Net/Net.h"
#include "Net/IpStack.h"
#include "Rtos/Types.h"

namespace Net
{
	//UDP dgrams from a specific ip/port, one dgram buffer
	class UdpDgramChannel : public DgramChannel
	{
	public:
		static void OnDgramReceived(void* arg, const ReadOnlyBuffer& buffer) { ((UdpDgramChannel*)arg)->OnDgramReceived(buffer); };

		UdpDgramChannel(const IpAddress& serverIp, const uint16_t serverPort, IpStack& stack, Buffer& buffer) :
			DgramChannel(),
			m_serverIp(serverIp),
			m_serverPort(serverPort),
			m_ipStack(stack),
			m_buffer(buffer)
		{
			m_ipStack.DgramReceived.Context = this;
			m_ipStack.DgramReceived.Handler = &UdpDgramChannel::OnDgramReceived;
		}


		virtual void Write(const ReadOnlyBuffer& buffer) override
		{
			m_ipStack.SendUdp(m_serverIp, m_serverPort, buffer);
		}

		virtual ReadOnlyBuffer Read() override
		{
			return { m_buffer.Data, m_buffer.Count };
		}

	private:
		void OnDgramReceived(const ReadOnlyBuffer& buffer)
		{
			//Strip IP and UDP header
			const IpHeader* ip = reinterpret_cast<const IpHeader*>(buffer.Data);
			Assert(buffer.Length == Net::ntohs(ip->TotalLength));
			const UdpHeader* udp = reinterpret_cast<const UdpHeader*>(ip + 1);

			//Copy into static buffer
			const ReadOnlyBuffer dgram = { (void*)(udp + 1), Net::ntohs(udp->Length) - sizeof(UdpHeader) };
			Assert(m_buffer.CopyFrom(dgram));

			//Signal
			if (DgramReceived.IsCallable())
				DgramReceived.Invoke();
		}

		const IpAddress& m_serverIp;
		const uint16_t m_serverPort;
		IpStack& m_ipStack;
		Buffer& m_buffer;
	};
}
