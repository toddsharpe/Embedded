#include "Stm32/GpioPin.h"
#include "Stm32/Nucleo-F746ZG.h"
#include "Rtos/Kernel.h"
#include "Net/Net.h"
#include "Net/IpStack.h"

using namespace Stm32;
using namespace Rtos;
using namespace Net;

extern NucleoF746ZG board;
extern Kernel kernel;

void OnDataReceived(void* sender, const ReadOnlyBuffer& buffer)
{
	board.Printf("Received packet\r\n");
	board.PrintBytes((char*)buffer.Data, buffer.Length);
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

	board.ip.DgramReceived.Context = nullptr;
	board.ip.DgramReceived.Handler = &OnDataReceived;

	board.Printf("EthernetTask\r\n");
	while (true)
	{
		board.ip.SendUdp(TelemIp, TelemPort, data);
		kernel.Sleep(5000);
	}
}
