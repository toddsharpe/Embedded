#pragma once

#include "Net/Net.h"

#include <cstddef>

extern void DebugPrintf(const char* format, ...);

namespace Net
{
	class ArpCache
	{
	public:
		ArpCache() :
			m_entries()
		{

		}

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
			DebugPrintf("ArpCache:\r\n");
			for (const Entry& entry : m_entries)
			{
				if (entry.Free())
				{
					DebugPrintf("    <free>\r\n");
				}
				else
				{
					DebugPrintf("    %d.%d.%d.%d -> %02X:%02X:%02X:%02X:%02X:%02X\r\n",
						entry.IpAddr.bytes[0], entry.IpAddr.bytes[1], entry.IpAddr.bytes[2], entry.IpAddr.bytes[3],
						entry.MacAddr.bytes[0], entry.MacAddr.bytes[1], entry.MacAddr.bytes[2], entry.MacAddr.bytes[3], entry.MacAddr.bytes[4], entry.MacAddr.bytes[5]);
				}
			}
		}

	private:
		static constexpr size_t MaxEntries = 8;

		struct Entry
		{
			IpAddress IpAddr;
			MacAddress MacAddr;

			bool Free() const
			{
				return IpAddr == IpAddress();
			}
		};

		Entry m_entries[MaxEntries];
	};
}
