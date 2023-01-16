#include <Windows.h>
#include <OTA.h>
#include <stdio.h>
#include <Assert.h>
#include <fstream>
#include <vector>
#include <shlwapi.h>
#include <RingBuffer.h>

static const std::string app = "..\\..\\build\\Stm32\App\\Nucleo.bin";

RingBuffer<uint8_t, 1024*1024> commBuffer;

int main()
{
	//Connect to comm
	HANDLE hComm = CreateFileA("COM4",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hComm == INVALID_HANDLE_VALUE)
	{
		printf("Error opening serial port\n");
		exit(-1);
	}
	printf("Opened serial port\n");
	
	//Build path to app
	TCHAR buffer[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, buffer);
	PathCombine(buffer, buffer, app.c_str());
	std::string appPath(buffer);

	//Read app
	std::ifstream appFile(appPath, std::ios_base::binary);
	std::vector<char>* appData = new std::vector<char>(std::istreambuf_iterator<char>(appFile), std::istreambuf_iterator<char>());
	size_t numberOfBlocks = (appData->size() + (OTA::DataSize - 1)) / OTA::DataSize;

	//TODO(tsharpe): Having a front pointer to a ring buffer is broken. For now, make it big.

	//Enter loop
	while (true)
	{
		uint8_t buffer[512];
		DWORD bytesRead = 0;

		if (!ReadFile(hComm, &buffer, sizeof(buffer), &bytesRead, NULL))
		{
			printf("ReadFile failed\n");
			exit(-1);
		}

		for (size_t i = 0; i < bytesRead; i++)
		{
			commBuffer.Write(buffer[i]);
		}

		if (commBuffer.Count() < sizeof(OTA::MessageHeader))
			continue;

		OTA::MessageHeader* header = (OTA::MessageHeader *)commBuffer.Front();
		if (commBuffer.Count() < header->Length)
			continue;

		printf("Received: %d\n", header->Type);
		switch (header->Type)
		{
		case OTA::MessageType::GetApp:
		{
			OTA::GetAppMessage* request = (OTA::GetAppMessage*)commBuffer.Front();
			
			OTA::AppInfoMessage response = {};
			response.Length = sizeof(OTA::AppInfoMessage);
			response.Type = OTA::MessageType::AppInfo;
			response.NumberOfBlocks = numberOfBlocks;

			DWORD bytesWritten = 0;
			if (!WriteFile(hComm, &response, sizeof(response), &bytesWritten, NULL))
			{
				printf("WriteFile failed\n");
				exit(-1);
			}
			AssertEqual(bytesWritten, sizeof(response));
		}
			break;

		case OTA::MessageType::GetDataBlock:
		{
			OTA::GetDataBlockMessage* request = (OTA::GetDataBlockMessage*)commBuffer.Front();
			printf("GetDataBlock - %d\n", request->BlockNumber);

			OTA::DataBlockMessage response = {};
			response.Type = OTA::MessageType::DataBlock;
			response.Length = sizeof(OTA::DataBlockMessage);
			response.BlockNumber = request->BlockNumber;

			size_t startIndex = request->BlockNumber * sizeof(response.Data);
			size_t length = std::min<size_t>((appData->size() - startIndex), sizeof(response.Data));

			memcpy(response.Data, appData->data() + startIndex, length);

			DWORD bytesWritten = 0;
			if (!WriteFile(hComm, &response, sizeof(response), &bytesWritten, NULL))
			{
				printf("WriteFile failed\n");
				exit(-1);
			}
			AssertEqual(bytesWritten, sizeof(response));
		}

			break;

		default:
			printf("Unknown message type %d\n", header->Type);
			exit(-1);
		}

		//Pop off message
		uint8_t dummy;
		for (size_t i = 0; i < header->Length; i++)
		{
			commBuffer.Read(dummy);
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
