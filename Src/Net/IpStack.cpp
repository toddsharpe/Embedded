#include <Board.h>
#include "Sys/EthMac.h"
#include "Net/IpStack.h"
#include "Buffer.h"
#include "Net/Net.h"
#include "Net/Checksum.h"
#include "Net/ArpCache.h"

namespace Net::IpStack
{
	static constexpr struct Net::IpAddress DefaultIpAddr = {{172, 26, 2, 1}};
	static constexpr struct Net::MacAddress DefaultMacAddr = {{0x02, 0x00, 0x01, 0x02, 0x03, 0x05}};

	//IP Buffers
	static StaticBuffer<EthMac::BufferSize> m_txBuffer;
	static StaticBuffer<EthMac::BufferSize> m_appBuffer;
	static bool m_buffered;

	Net::IpAddress IpAddr = DefaultIpAddr;
	Net::MacAddress MacAddr = DefaultMacAddr;

	ParamCallback<const ReadOnlyBuffer&> DgramReceived;

	static bool GetMac(const Net::IpAddress& ipAddr, Net::MacAddress& macAddr)
	{
		if (IsMulticast(ipAddr))
		{
			macAddr = GetMulticastMac(ipAddr);
			return true;
		}
		else
			return Net::ArpCache::Lookup(ipAddr, macAddr);
	}

	//Handlers
	static void HandleArpRequest(const ArpPacket& packet)
	{
		//Check if target is us
		if (packet.TargetIp != IpAddr)
			return;

		//Packet storage
		const size_t packet_size = sizeof(EthHeader) + sizeof(ArpPacket);
		Assert(packet_size <= m_txBuffer.Length);
		m_txBuffer.Count = packet_size;

		EthHeader* eth = reinterpret_cast<EthHeader*>(m_txBuffer.Data);
		eth->Dest = Broadcast;
		eth->Source = MacAddr;
		eth->type = (EtherType)Net::htons(EtherType::ARP);

		//Build reply
		ArpPacket* reply = reinterpret_cast<ArpPacket*>(eth + 1);
		reply->HardwareType = packet.HardwareType;
		reply->ProtocolType = packet.ProtocolType;
		reply->HardwareSize = packet.HardwareSize;
		reply->ProtocolSize = packet.ProtocolSize;
		reply->Op = (ArpOp)Net::htons(ArpOp::Reply);
		reply->SenderMac = MacAddr;
		reply->SenderIp = IpAddr;
		reply->TargetMac = packet.SenderMac;
		reply->TargetIp = packet.SenderIp;

		//Send
		EthMac::Send(m_txBuffer);
	}

	static void HandleArpReply(const ArpPacket& arp)
	{
		//Check if target is us
		if (arp.TargetIp != IpAddr)
			return;

		//Update cache
		Assert(ArpCache::Insert(arp.SenderIp, arp.SenderMac));
		ArpCache::Display();

		//Send buffered packet
		if (m_buffered)
		{
			//Update ARP
			EthHeader* eth = reinterpret_cast<EthHeader*>(m_appBuffer.Data);
			eth->Dest = arp.SenderMac;
			
			EthMac::Send(m_appBuffer);
			m_buffered = false;
		}
	}

	static void HandleEchoRequest(const ReadOnlyBuffer& request)
	{
		//Inspect request
		const EthHeader* requestEth = reinterpret_cast<const EthHeader*>(request.Data);
		const IpHeader* requestIp = reinterpret_cast<const IpHeader*>(requestEth + 1);
		const EchoPacket* echo = reinterpret_cast<const EchoPacket*>(requestIp + 1);

		const size_t packetSize = Net::ntohs(requestIp->TotalLength);
		Assert(packetSize > sizeof(IpHeader) + sizeof(EchoPacket));
		const size_t payloadSize = packetSize - sizeof(IpHeader) - sizeof(EchoPacket);

		//Packet storage. Reply is same size as request.
		m_txBuffer.Count = sizeof(EthHeader) + packetSize;

		//Set ethernet destination
		EthHeader* eth = reinterpret_cast<EthHeader*>(m_txBuffer.Data);
		Assert(GetMac(requestIp->Source, eth->Dest));
		eth->Source = MacAddr;
		eth->type = (EtherType)Net::htons(EtherType::IPv4);

		//Populate out IP header
		IpHeader* ip = reinterpret_cast<IpHeader*>(eth + 1);
		ip->Version = 4;
		ip->IHL = sizeof(IpHeader) / sizeof(uint32_t);
		ip->DSCP = 0;
		ip->TotalLength = Net::htons(m_txBuffer.Count - sizeof(EthHeader));
		ip->Identification = 0;
		ip->Flags = 0;
		ip->FragmentOffset = 0;
		ip->TimeToLive = 64;
		ip->Protocol = IpProtocol::ICMP;
		ip->HeaderChecksum = 0;
		ip->Source = IpAddr;
		ip->Dest = requestIp->Source;
		ip->HeaderChecksum = Checksum::Compute(ip, sizeof(IpHeader));

		//Populate echo packet
		EchoPacket* icmp = reinterpret_cast<EchoPacket*>(ip + 1);
		icmp->Header.Type = IcmpType::EchoReply;
		icmp->Header.Code = 0;
		icmp->Header.Checksum = 0;
		icmp->Identifier = echo->Identifier;
		icmp->SequenceNumber = echo->SequenceNumber;
		//RCF 792: The data received in the echo message must be returned in the echo reply message.
		memcpy(icmp->Payload, echo->Payload, payloadSize);

		//Populate checksum of ICMP headers and data
		icmp->Header.Checksum = Checksum::Compute(icmp, sizeof(EchoPacket) + payloadSize);

		//Send
		EthMac::Send(m_txBuffer);
	}

	static void SendArpRequest(const IpAddress& ipAddr)
	{
		Board::Printf("SendArpRequest\r\n");
		
		const size_t packet_size = sizeof(EthHeader) + sizeof(ArpPacket);
		Assert(packet_size <= m_txBuffer.Length);
		m_txBuffer.Count = packet_size;

		EthHeader* eth = reinterpret_cast<EthHeader*>(m_txBuffer.Data);
		eth->Dest = Broadcast;
		eth->Source = IpStack::MacAddr;
		eth->type = (EtherType)Net::htons(EtherType::ARP);

		//Build request
		ArpPacket* request = reinterpret_cast<ArpPacket*>(eth + 1);
		request->HardwareType = (ArpHardwareType)Net::htons(ArpHardwareType::Ethernet);
		request->ProtocolType = (EtherType)Net::htons(EtherType::IPv4);
		request->HardwareSize = sizeof(MacAddress);
		request->ProtocolSize = sizeof(IpAddress);
		request->Op = (ArpOp)Net::htons(ArpOp::Request);
		request->SenderMac = MacAddr;
		request->SenderIp = IpAddr;
		request->TargetMac = Broadcast;
		request->TargetIp = ipAddr;

		//Send
		EthMac::Send(m_txBuffer);
	}

	void Init()
	{
		//Register handlers
		EthMac::FrameReceived = { nullptr, &OnFrameReceived };
	}

	void SendUdp(const IpAddress& host, const uint16_t port, const ReadOnlyBuffer& buffer)
	{
		const size_t packet_size = sizeof(EthHeader) + sizeof(IpHeader) + sizeof(UdpHeader) + buffer.Length;
		Assert(packet_size <= m_txBuffer.Length);
		m_txBuffer.Count = packet_size;

		//Set ethernet destination
		EthHeader* eth = reinterpret_cast<EthHeader*>(m_txBuffer.Data);
		const bool resolved = GetMac(host, eth->Dest);
		eth->Source = MacAddr;
		eth->type = (EtherType)Net::htons(EtherType::IPv4);

		//Populate out IP header
		IpHeader* ip = reinterpret_cast<IpHeader*>(eth + 1);
		ip->Version = 4;
		ip->IHL = sizeof(IpHeader) / sizeof(uint32_t);
		ip->DSCP = 0;
		ip->TotalLength = Net::htons(packet_size - sizeof(EthHeader));
		ip->Identification = 0;
		ip->Flags = 0;
		ip->FragmentOffset = 0;
		ip->TimeToLive = 64;
		ip->Protocol = IpProtocol::UDP;
		ip->HeaderChecksum = 0;
		ip->Source = IpAddr;
		ip->Dest = host;
		ip->HeaderChecksum = Checksum::Compute(ip, sizeof(IpHeader));

		//Populate udp header
		UdpHeader* udp = reinterpret_cast<UdpHeader*>(ip + 1);
		udp->SourcePort = Net::htons(port);
		udp->DestPort = Net::htons(port);
		udp->Length = Net::htons(sizeof(UdpHeader) + buffer.Length);
		udp->Checksum = 0;

		//Copy in data
		memcpy(udp + 1, buffer.Data, buffer.Length);

		//Calculate checksum, using the Ipv4 pseudo header
		//https://en.wikipedia.org/wiki/User_Datagram_Protocol#IPv4_pseudo_header
		Checksum checksum;
		checksum.Add(&ip->Source, sizeof(IpAddress));
		checksum.Add(&ip->Dest, sizeof(IpAddress));
		checksum.Add(ip->Protocol);
		checksum.Add(sizeof(UdpHeader) + buffer.Length);
		checksum.Add(udp, sizeof(UdpHeader) + buffer.Length);
		udp->Checksum = checksum.Get();

		if (resolved)
		{
			//Send
			EthMac::Send(m_txBuffer);
		}
		else
		{
			//Buffer packet
			m_buffered = true;
			Assert(m_appBuffer.CopyFrom(m_txBuffer));

			//Send ARP request
			SendArpRequest(host);
		}
	}

	void OnFrameReceived(void* arg, const ReadOnlyBuffer& buffer)
	{
		const EthHeader* eth = reinterpret_cast<const EthHeader*>(buffer.Data);
		const EtherType type = (EtherType)Net::ntohs(eth->type);
		switch (type)
		{
			case Net::EtherType::ARP:
			{
				const ArpPacket* arp = reinterpret_cast<const ArpPacket*>(eth + 1);
				AssertEqual(Net::ntohs(arp->ProtocolType), Net::EtherType::IPv4);

				const ArpOp op = (ArpOp)Net::ntohs(arp->Op);
				if (op == ArpOp::Request)
					HandleArpRequest(*arp);
				else if (op == ArpOp::Reply)
					HandleArpReply(*arp);
				else
					AssertPrintHex32(false, op);
			}
			break;

			case Net::EtherType::IPv4:
			{
				const IpHeader* ip = reinterpret_cast<const IpHeader*>(eth + 1);

				//Oppertunistically, populate ARP cache
				if (!ArpCache::Contains(ip->Source))
				{
					Assert(ArpCache::Insert(ip->Source, eth->Source));
					ArpCache::Display();
				}

				switch (ip->Protocol)
				{
					case IpProtocol::ICMP:
					{
						const IcmpHeader* icmp = reinterpret_cast<const IcmpHeader*>(ip + 1);
						const IcmpType type = (IcmpType)icmp->Type;
						switch (type)
						{
							case IcmpType::EchoRequest:
								HandleEchoRequest(buffer);
								break;

							case IcmpType::DestUnreachable:
								Board::Printf("Destination Unreachable\r\n");
								break;

							default:
								Board::Printf("Unknown ICMP type: %d\r\n", type);
								break;
						}
					}
					break;

					case IpProtocol::UDP:
						if (DgramReceived.IsCallable())
						{
							const ReadOnlyBuffer data = {ip, Net::ntohs(ip->TotalLength)};
							DgramReceived.Invoke(data);
						}
						break;

					default:
						Board::Printf("Unknown IP protocol: %d\r\n", ip->Protocol);
						break;
				}
			}
			break;

			default:
				Board::Printf("Unknown ether type 0x%x\r\n", type);
				break;
		}
	}

	void Display()
	{
		Board::Printf("IpStack: %d.%d.%d.%d\r\n", IpAddr.bytes[0], IpAddr.bytes[1], IpAddr.bytes[2], IpAddr.bytes[3]);
	}
}
