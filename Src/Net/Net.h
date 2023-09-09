#pragma once

#include "Assert.h"

#include <cstdint>
#include <cstring>
#include <cstddef>

// https://inc0x0.com/tcp-ip-packets-introduction/tcp-ip-packets-3-manually-create-and-send-raw-tcp-ip-packets/
namespace Net
{
	struct __attribute__((packed)) MacAddress
	{
		uint8_t bytes[6];
	};
	static constexpr MacAddress Broadcast = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};

	enum EtherType : uint16_t
	{
		IPv4 = 0x0800,
		ARP = 0x0806,
	};

	struct __attribute__((packed)) EthHeader
	{
		MacAddress Dest;
		MacAddress Source;
		EtherType type;
	};
	static_assert(sizeof(EthHeader) == 14, "Invalid size");

	struct __attribute__((packed)) IpAddress
	{
		uint8_t bytes[4];

		bool operator==(const IpAddress &other) const
		{
			return bytes[0] == other.bytes[0] &&
				   bytes[1] == other.bytes[1] &&
				   bytes[2] == other.bytes[2] &&
				   bytes[3] == other.bytes[3];
		}

		bool operator!=(const IpAddress &other) const
		{
			return !(*this == other);
		}
	};

	enum IpProtocol : uint8_t
	{
		ICMP = 1,
		IGMP = 2,
		TCP = 6,
		UDP = 17,
	};

	struct __attribute__((packed)) IpHeader
	{
		uint8_t IHL : 4;
		uint8_t Version : 4;
		uint8_t DSCP;
		uint16_t TotalLength;
		uint16_t Identification;
		uint16_t FragmentOffset : 13;
		uint16_t Flags : 3;
		uint8_t TimeToLive;
		IpProtocol Protocol;
		uint16_t HeaderChecksum;
		IpAddress Source;
		IpAddress Dest;
	};
	static_assert(sizeof(IpHeader) == 20, "Invalid size");

	struct __attribute__((packed)) UdpHeader
	{
		uint16_t SourcePort;
		uint16_t DestPort;
		uint16_t Length;
		uint16_t Checksum;
	};
	static_assert(sizeof(UdpHeader) == 8, "Invalid size");

	enum ArpOp : uint16_t
	{
		Request = 1,
		Reply = 2,
	};

	struct __attribute__((packed)) ArpPacket
	{
		uint16_t HardwareType;
		EtherType ProtocolType;
		uint8_t HardwareSize;
		uint8_t ProtocolSize;
		ArpOp Op;
		MacAddress SenderMac;
		IpAddress SenderIp;
		MacAddress TargetMac;
		IpAddress TargetIp;
	};
	static_assert(sizeof(ArpPacket) == 28, "Invalid size");

	enum class IcmpType : uint8_t
	{
		EchoReply = 0,
		EchoRequest = 8,
	};

	struct __attribute__((packed)) IcmpHeader
	{
		IcmpType Type;
		uint8_t Code;
		uint16_t Checksum;
	};
	static_assert(sizeof(IcmpHeader) == 4, "Invalid size");

	struct __attribute__((packed)) EchoPacket
	{
		IcmpHeader Header;
		uint16_t Identifier;
		uint16_t SequenceNumber;
		uint8_t Payload[];
	};
	static_assert(sizeof(EchoPacket) == 8, "Invalid size");

	static constexpr bool IsMulticast(const IpAddress &addr)
	{
		return (addr.bytes[0] & 0xF0) == 0xE0;
	}

	// https://support.huawei.com/enterprise/en/doc/EDOC1100127200/d30cdf7f/overview-of-multicast-mac-addresses
	static constexpr MacAddress GetMulticastMac(const IpAddress &addr)
	{
		Assert(IsMulticast(addr));
		return {{0x01, 0x00, 0x5E, (uint8_t)(addr.bytes[1] & 0x7F), addr.bytes[2], addr.bytes[3]}};
	}

	// Network byte order conversions. Only supported from little-endian targets.
	static_assert(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__, "Invalid byte order");
	static constexpr uint16_t htons(uint16_t value)
	{
		return ((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8);
	}

	static constexpr uint16_t ntohs(uint16_t value)
	{
		return htons(value);
	}

	//http://www.faqs.org/rfcs/rfc1071.html Section 4.1
	//http://www.microhowto.info/howto/calculate_an_internet_protocol_checksum_in_c.html
	//Input and output in network byte order (big-endian)
	static inline uint16_t IpChecksum(const void* vdata, const size_t length)
	{
		// Cast the data pointer to one that can be indexed.
		char* data = (char*)vdata;

		// Initialise the accumulator.
		uint32_t acc = 0xffff;

		// Handle complete 16-bit blocks.
		for (size_t i = 0; i + 1 < length; i += 2) {
			uint16_t word;
			memcpy(&word, data + i, 2);
			acc += word;
			if (acc > 0xffff) {
				acc -= 0xffff;
			}
		}

		// Handle any partial block at the end of the data.
		if (length & 1) {
			uint16_t word = 0;
			memcpy(&word, data + length - 1, 1);
			acc += word;
			if (acc > 0xffff) {
				acc -= 0xffff;
			}
		}

		// Return the checksum in network byte order.
		return ~acc;
	}
}
