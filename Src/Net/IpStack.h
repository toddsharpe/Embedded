#pragma once

#include "Sys/EthMac.h"
#include "Rtos/Types.h"
#include "Net/Net.h"
#include "Net/Checksum.h"
#include "Net/ArpCache.h"

namespace Net
{
	//TODO(tsharpe): Handle timeouts / retries
	class IpStack
	{
	public:
		static void OnFrameReceived(void* arg, const ReadOnlyBuffer& buffer) { ((IpStack*)arg)->OnFrameReceived(buffer); };

		IpStack(Sys::EthMac& mac) :
			IpAddr(DefaultIpAddr),
			MacAddr(DefaultMacAddr),
			DgramReceived(),
			m_mac(mac),
			m_txBuffer(),
			m_buffered(),
			m_SysBuffer(),
			m_cache()
		{
			//Frame callback
			m_mac.FrameReceived.Context = this;
			m_mac.FrameReceived.Handler = &IpStack::OnFrameReceived;
		}

		//NOTE(tsharpe): Hack around global static initializer dependencies. Fix?
		void InitBuffers(Buffer& txBuffer, Buffer& sysBuffer)
		{
			m_txBuffer = txBuffer;
			m_SysBuffer = sysBuffer;
		}

		void Display()
		{
			DebugPrintf("IpStack: %d.%d.%d.%d\r\n", IpAddr.bytes[0], IpAddr.bytes[1], IpAddr.bytes[2], IpAddr.bytes[3]);
		}

		void SendUdp(const IpAddress& host, const uint16_t port, const ReadOnlyBuffer& buffer)
		{
			const size_t packet_size = sizeof(EthHeader) + sizeof(IpHeader) + sizeof(UdpHeader) + buffer.Length;
			Assert(packet_size <= m_txBuffer.Length);
			m_txBuffer.Count = packet_size;

			//Set ethernet destination
			EthHeader* eth = reinterpret_cast<EthHeader*>(m_txBuffer.Data);
			const bool resolved = GetMac(host, eth->Dest);
			eth->Source = this->MacAddr;
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
			ip->Source = this->IpAddr;
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
				m_mac.Send(m_txBuffer);
			}
			else
			{
				//Buffer packet
				m_buffered = true;
				Assert(m_SysBuffer.CopyFrom(m_txBuffer));

				//Send ARP request
				SendArpRequest(host);
			}
		}

		void OnFrameReceived(const ReadOnlyBuffer& buffer)
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
					if (!m_cache.Contains(ip->Source))
					{
						Assert(m_cache.Insert(ip->Source, eth->Source));
						m_cache.Display();
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

								default:
									DebugPrintf("Unknown ICMP type: %d\r\n", type);
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
							DebugPrintf("Unknown IP protocol: %d\r\n", ip->Protocol);
							break;
					}
				}
				break;

				default:
					DebugPrintf("Unknown ether type 0x%x\r\n", Net::ntohs(type));
					break;
			}
		};

		IpAddress IpAddr;
		Net::MacAddress MacAddr;
		ParamCallback<const ReadOnlyBuffer&> DgramReceived;

	private:
		static constexpr struct IpAddress DefaultIpAddr = {{172, 26, 2, 1}};
		static constexpr struct Net::MacAddress DefaultMacAddr = {{0x02, 0x00, 0x01, 0x02, 0x03, 0x05}};

		void SendArpRequest(const IpAddress& ipAddr)
		{
			const size_t packet_size = sizeof(EthHeader) + sizeof(ArpPacket);
			Assert(packet_size <= m_txBuffer.Length);
			m_txBuffer.Count = packet_size;

			EthHeader* eth = reinterpret_cast<EthHeader*>(m_txBuffer.Data);
			eth->Dest = Broadcast;
			eth->Source = this->MacAddr;
			eth->type = (EtherType)Net::htons(EtherType::ARP);

			//Build request
			ArpPacket* request = reinterpret_cast<ArpPacket*>(eth + 1);
			request->HardwareType = (ArpHardwareType)Net::htons(ArpHardwareType::Ethernet);
			request->ProtocolType = (EtherType)Net::htons(EtherType::IPv4);
			request->HardwareSize = sizeof(MacAddress);
			request->ProtocolSize = sizeof(IpAddress);
			request->Op = (ArpOp)Net::htons(ArpOp::Request);
			request->SenderMac = this->MacAddr;
			request->SenderIp = this->IpAddr;
			request->TargetMac = Broadcast;
			request->TargetIp = ipAddr;

			//Send
			m_mac.Send(m_txBuffer);
		}

		void HandleArpRequest(const ArpPacket& packet)
		{
			//Check if target is us
			if (packet.TargetIp != this->IpAddr)
				return;

			//Packet storage
			const size_t packet_size = sizeof(EthHeader) + sizeof(ArpPacket);
			Assert(packet_size <= m_txBuffer.Length);
			m_txBuffer.Count = packet_size;

			EthHeader* eth = reinterpret_cast<EthHeader*>(m_txBuffer.Data);
			eth->Dest = Broadcast;
			eth->Source = this->MacAddr;
			eth->type = (EtherType)Net::htons(EtherType::ARP);

			//Build reply
			ArpPacket* reply = reinterpret_cast<ArpPacket*>(eth + 1);
			reply->HardwareType = packet.HardwareType;
			reply->ProtocolType = packet.ProtocolType;
			reply->HardwareSize = packet.HardwareSize;
			reply->ProtocolSize = packet.ProtocolSize;
			reply->Op = (ArpOp)Net::htons(ArpOp::Reply);
			reply->SenderMac = this->MacAddr;
			reply->SenderIp = this->IpAddr;
			reply->TargetMac = packet.SenderMac;
			reply->TargetIp = packet.SenderIp;

			//Send
			m_mac.Send(m_txBuffer);
		}

		void HandleArpReply(const ArpPacket& arp)
		{
			//Check if target is us
			if (arp.TargetIp != this->IpAddr)
				return;

			//Update cache
			Assert(m_cache.Insert(arp.SenderIp, arp.SenderMac));
			m_cache.Display();

			//Send buffered packet
			if (m_buffered)
			{
				//Update ARP
				EthHeader* eth = reinterpret_cast<EthHeader*>(m_SysBuffer.Data);
				eth->Dest = arp.SenderMac;
				
				m_mac.Send(m_SysBuffer);
				m_buffered = false;
			}
		}

		void HandleEchoRequest(const ReadOnlyBuffer& request)
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
			eth->Source = this->MacAddr;
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
			ip->Source = this->IpAddr;
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
			m_mac.Send(m_txBuffer);
		}

		bool GetMac(const IpAddress& ipAddr, MacAddress& macAddr)
		{
			if (IsMulticast(ipAddr))
			{
				macAddr = GetMulticastMac(ipAddr);
				return true;
			}
			else
				return m_cache.Lookup(ipAddr, macAddr);
		}

		Sys::EthMac& m_mac;
		Buffer m_txBuffer;
		bool m_buffered;
		Buffer m_SysBuffer;
		ArpCache m_cache;
	};
}
