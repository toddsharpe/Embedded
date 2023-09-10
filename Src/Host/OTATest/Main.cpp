#include "OTA.h"
#include "Host/UdpClient.h"

#include <iostream>
#include <cstdarg>

using namespace OTA;
using namespace Host;
using namespace std;

int main()
{
	cout << "OTA Test" << endl;
	UdpClient client(OTA::Server, OTA::Port);
	client.Init();

	GetAppMessage request = {};
	request.Length = sizeof(GetAppMessage);
	request.Type = MessageType::GetApp;
	AppInfoMessage response = {};
	client.SendAndReceive(request, response);
	cout << "App size: " << response.NumberOfBlocks << endl;
}

void Bugcheck(const char* file, const char* line, const char* format, ...)
{
	printf("Kernel Bugcheck\r\n");
	printf("\r\n%s\r\n%s\r\n", file, line);

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	printf("\r\n");
	va_end(args);

	exit(-1);
}
