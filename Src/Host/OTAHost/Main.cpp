#include "RingBuffer.h"
#include "Host/UdpServer.h"
#include "OTA.h"
#include "Assert.h"

#include <cstdarg>
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <limits.h>

static const std::string app = "/../build/Stm32/Nucleo/Nucleo.bin";

using namespace Host;

int main()
{
	std::cout << "OTAHost" << std::endl;
	
	UdpServer server(OTA::Port);
	server.Init();
	std::cout << "Listening on port " << OTA::Port << std::endl;
	
	//Build path
	char cwd[PATH_MAX];
	Assert(getcwd(cwd, sizeof(cwd)));
	std::string appPath = std::string(cwd) + app;
	std::cout << "App path: " << appPath << std::endl;

	//Read app
	std::ifstream appFile(appPath, std::ios_base::binary);
	Assert(appFile.is_open());
	std::vector<char>* appData = new std::vector<char>(std::istreambuf_iterator<char>(appFile), std::istreambuf_iterator<char>());
	const size_t numberOfBlocks = (appData->size() + (OTA::DataSize - 1)) / OTA::DataSize;
	std::cout << "App size: " << appData->size() << "  blocks: " << numberOfBlocks << std::endl;

	//Enter loop
	while (true)
	{
		uint8_t buffer[512];
		const size_t bytesRead = server.Receive(buffer, sizeof(buffer));
		Assert(bytesRead >= sizeof(OTA::MessageHeader));

		const OTA::MessageHeader* const header = (OTA::MessageHeader *)buffer;
		Assert(bytesRead == header->Length);

		switch (header->Type)
		{
			case OTA::MessageType::GetApp:
			{
				std::cout << "  GetApp" << std::endl;
				const OTA::GetAppMessage* const request = (const OTA::GetAppMessage* const)header;
				
				OTA::AppInfoMessage response = {};
				response.Length = sizeof(OTA::AppInfoMessage);
				response.Type = OTA::MessageType::AppInfo;
				response.NumberOfBlocks = numberOfBlocks;

				server.Send(&response, sizeof(response));
			}
			break;

			case OTA::MessageType::GetDataBlock:
			{
				const OTA::GetDataBlockMessage* const request = (const OTA::GetDataBlockMessage* const)header;
				std::cout << "  GetDataBlock - " << request->BlockNumber << std::endl;

				OTA::DataBlockMessage response = {};
				response.Type = OTA::MessageType::DataBlock;
				response.Length = sizeof(OTA::DataBlockMessage);
				response.BlockNumber = request->BlockNumber;

				const size_t startIndex = request->BlockNumber * sizeof(response.Data);
				const size_t length = std::min<size_t>((appData->size() - startIndex), sizeof(response.Data));
				memcpy(response.Data, appData->data() + startIndex, length);

				server.Send(&response, sizeof(response));
			}
			break;

			default:
				std::cout << "  Unknown message type " << header->Type << std::endl;
				exit(-1);
		}
	}

	return 0;
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
