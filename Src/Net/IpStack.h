#pragma once

#include <Board.h>
#include "Sys/EthMac.h"
#include "Buffer.h"
#include "Net/Net.h"
#include "Net/Checksum.h"
#include "Net/ArpCache.h"

//TODO(tsharpe): Handle timeouts / retries
namespace Net::IpStack
{
	void Init();
	void SendUdp(const IpAddress& host, const uint16_t port, const ReadOnlyBuffer& buffer);
	void OnFrameReceived(void* arg, const ReadOnlyBuffer& buffer);
	void Display();

	extern Net::IpAddress IpAddr;
	extern Net::MacAddress MacAddr;
	extern ParamCallback<const ReadOnlyBuffer&> DgramReceived;
}
