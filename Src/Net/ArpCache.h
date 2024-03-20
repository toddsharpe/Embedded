#pragma once

#include "Net/Net.h"

#include <cstddef>

namespace Net::ArpCache
{
	bool Insert(const IpAddress& ipAddr, const MacAddress& macAddr);
	bool Contains(const IpAddress& ipAddr);
	bool Lookup(const IpAddress& ipAddr, MacAddress& macAddr);

	void Display();
}
