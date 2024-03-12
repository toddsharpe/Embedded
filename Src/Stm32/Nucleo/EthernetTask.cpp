#include "Buffer.h"
#include "Rtos/Kernel.h"
#include "Net/Net.h"
#include "Net/IpStack.h"

using namespace Rtos;
using namespace Net;

void OnDataReceived(void* sender, const ReadOnlyBuffer& buffer)
{
	Board::Printf("Received packet\r\n");
	Board::PrintBytes((char*)buffer.Data, buffer.Length);
}

void EthernetTask()
{
	//Destination
	const uint16_t TelemPort = 8080;
	const IpAddress TelemIp = {{239, 1, 1, 1}};

	//Data
	ReadOnlyBuffer data;
	data.Data = (uint8_t*)"Hello, world!";
	data.Length = 13;

	Net::IpStack::DgramReceived = { nullptr, &OnDataReceived };

	Board::Printf("EthernetTask\r\n");
	while (true)
	{
		IpStack::SendUdp(TelemIp, TelemPort, data);
		Rtos::SleepThread(5000);
	}
}
