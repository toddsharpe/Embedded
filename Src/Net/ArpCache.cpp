#include "Net/Net.h"
#include "Board.h"

#include <cstddef>

namespace
{
	static constexpr size_t MaxEntries = 8;

	struct Entry
	{
		Net::IpAddress IpAddr;
		Net::MacAddress MacAddr;

		bool Free() const
		{
			return IpAddr == Net::IpAddress();
		}
	};
	Entry m_entries[MaxEntries];
}

namespace Net::ArpCache
{
	bool Insert(const IpAddress& ipAddr, const MacAddress& macAddr)
	{
		for (Entry& entry : m_entries)
		{
			if (!entry.Free())
				continue;

			entry.IpAddr = ipAddr;
			entry.MacAddr = macAddr;
			return true;
		}

		return false;
	}

	bool Contains(const IpAddress& ipAddr)
	{
		for (const Entry& entry : m_entries)
		{
			if (entry.IpAddr == ipAddr)
				return true;
		}

		return false;
	}

	bool Lookup(const IpAddress& ipAddr, MacAddress& macAddr)
	{
		for (const Entry& entry : m_entries)
		{
			if (entry.IpAddr == ipAddr)
			{
				macAddr = entry.MacAddr;
				return true;
			}
		}

		return false;
	}

	void Display()
	{
		Board::Printf("ArpCache:\r\n");
		for (const Entry& entry : m_entries)
		{
			if (entry.Free())
			{
				Board::Printf("    <free>\r\n");
			}
			else
			{
				Board::Printf("    %d.%d.%d.%d -> %02X:%02X:%02X:%02X:%02X:%02X\r\n",
					entry.IpAddr.bytes[0], entry.IpAddr.bytes[1], entry.IpAddr.bytes[2], entry.IpAddr.bytes[3],
					entry.MacAddr.bytes[0], entry.MacAddr.bytes[1], entry.MacAddr.bytes[2], entry.MacAddr.bytes[3], entry.MacAddr.bytes[4], entry.MacAddr.bytes[5]);
			}
		}
	}
}
