#pragma once

#include "Sys/EthMac.h"
#include "Rtos/Types.h"
#include "Net/Net.h"
#include "Net/ArpCache.h"

extern void DebugPrintBytes(const char* buffer, const size_t length);

namespace Net
{
	class IpStack
	{
	public:
		static void OnFrameReceived(void* arg, const Buffer& buffer) { ((IpStack*)arg)->OnFrameReceived(buffer); };

		IpStack(Sys::EthMac& mac) :
			IpAddr(DefaultIpAddr),
			MacAddr(DefaultMacAddr),
			m_mac(mac),
			m_cache()
		{
			//Frame callback
			m_mac.FrameReceived.Context = this;
			m_mac.FrameReceived.Handler = &IpStack::OnFrameReceived;
		}

		void Display()
		{
			DebugPrintf("IpStack: %d.%d.%d.%d\r\n", IpAddr.bytes[0], IpAddr.bytes[1], IpAddr.bytes[2], IpAddr.bytes[3]);
			m_mac.Display();
		}

		ParamCallback<const Buffer&> DgramReceived;

		void SendUdp(const IpAddress& host, const uint16_t port, const ReadOnlyBuffer& buffer)
		{
			uint8_t packet[sizeof(EthHeader) + sizeof(IpHeader) + sizeof(UdpHeader) + buffer.Length];

			//Set ethernet destination
			EthHeader* eth = reinterpret_cast<EthHeader*>(packet);
			Assert(GetMac(host, eth->Dest));
			eth->Source = this->MacAddr;
			eth->type = (EtherType)Net::htons(EtherType::IPv4);

			//Populate out IP header
			IpHeader* ip = reinterpret_cast<IpHeader*>(eth + 1);
			ip->Version = 4;
			ip->IHL = sizeof(IpHeader) / sizeof(uint32_t);
			ip->DSCP = 0;
			ip->TotalLength = Net::htons(sizeof(packet) - sizeof(EthHeader));
			ip->Identification = 0;
			ip->Flags = 0;
			ip->FragmentOffset = 0;
			ip->TimeToLive = 64;
			ip->Protocol = IpProtocol::UDP;
			ip->HeaderChecksum = 0;
			ip->Source = this->IpAddr;
			ip->Dest = host;

			//Populate udp header
			UdpHeader* udp = reinterpret_cast<UdpHeader*>(ip + 1);
			udp->SourcePort = 0;
			udp->DestPort = Net::htons(port);
			udp->Length = Net::htons(sizeof(UdpHeader) + buffer.Length);
			udp->Checksum = 0;

			//Copy in data
			memcpy(udp + 1, buffer.Data, buffer.Length);

			//Send
			m_mac.Send(packet, sizeof(packet));
		}

		void OnFrameReceived(const Buffer& buffer)
		{
			const EthHeader* eth = reinterpret_cast<EthHeader*>(buffer.Data);
			const EtherType type = (EtherType)Net::ntohs(eth->type);
			switch (type)
			{
				case Net::EtherType::ARP:
				{
					DebugPrintf("ARP\r\n");
					const ArpPacket* arp = reinterpret_cast<const ArpPacket*>(eth + 1);
					AssertEqual(Net::ntohs(arp->ProtocolType), Net::EtherType::IPv4);
					HandleArp(*arp);
				}
				break;

				case Net::EtherType::IPv4:
				{
					DebugPrintf("IPv4\r\n");
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
								const UdpHeader* udp = reinterpret_cast<const UdpHeader*>(ip + 1);
								const Buffer data = { (void*)(udp + 1), Net::ntohs(udp->Length) - sizeof(UdpHeader) };
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
					DebugPrintf("Unknown ether type %d\r\n", Net::ntohs(type));
					break;
			}
		};

		IpAddress IpAddr;
		Net::MacAddress MacAddr;

	private:
		static constexpr struct IpAddress DefaultIpAddr = {{172, 26, 2, 1}};
		static constexpr struct Net::MacAddress DefaultMacAddr = {{0x02, 0x00, 0x01, 0x02, 0x03, 0x05}};

		void HandleArp(const ArpPacket& packet)
		{
			//Check if target is us
			if (packet.TargetIp != this->IpAddr)
				return;

			//Packet storage
			uint8_t buffer[sizeof(EthHeader) + sizeof(ArpPacket)];

			EthHeader* eth = reinterpret_cast<EthHeader*>(buffer);
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
			m_mac.Send(buffer, sizeof(buffer));
		}

		void HandleEchoRequest(const Buffer& request)
		{
			//Inspect request
			const EthHeader* requestEth = reinterpret_cast<EthHeader*>(request.Data);
			const IpHeader* requestIp = reinterpret_cast<const IpHeader*>(requestEth + 1);
			const EchoPacket* echo = reinterpret_cast<const EchoPacket*>(requestIp + 1);

			const size_t packetSize = Net::ntohs(requestIp->TotalLength);
			Assert(packetSize > sizeof(IpHeader) + sizeof(EchoPacket));
			const size_t payloadSize = packetSize - sizeof(IpHeader) - sizeof(EchoPacket);

			//Packet storage. Reply is same size as request.
			uint8_t buffer[sizeof(EthHeader) + packetSize];

			//Set ethernet destination
			EthHeader* eth = reinterpret_cast<EthHeader*>(buffer);
			Assert(GetMac(requestIp->Source, eth->Dest));
			eth->Source = this->MacAddr;
			eth->type = (EtherType)Net::htons(EtherType::IPv4);

			//Populate out IP header
			IpHeader* ip = reinterpret_cast<IpHeader*>(eth + 1);
			ip->Version = 4;
			ip->IHL = sizeof(IpHeader) / sizeof(uint32_t);
			ip->DSCP = 0;
			ip->TotalLength = Net::htons(sizeof(buffer) - sizeof(EthHeader));
			ip->Identification = 0;
			ip->Flags = 0;
			ip->FragmentOffset = 0;
			ip->TimeToLive = 64;
			ip->Protocol = IpProtocol::ICMP;
			ip->HeaderChecksum = 0;
			ip->Source = this->IpAddr;
			ip->Dest = requestIp->Source;
			ip->HeaderChecksum = Net::IpChecksum(ip, sizeof(IpHeader));

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
			icmp->Header.Checksum = Net::IpChecksum(icmp, sizeof(EchoPacket) + payloadSize);

			//Send
			m_mac.Send(buffer, sizeof(buffer));
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

		//TODO(tsharpe): ARP cache

		Sys::EthMac& m_mac;
		ArpCache m_cache;
	};
}
