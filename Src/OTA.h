#pragma once

#include <stdint.h>

//Client: Get App
//Server: App size, # of blocks

//Client: Get block #
//Server: Data block#

namespace OTA
{
	static constexpr size_t DataSize = 512;
	
	enum MessageType : uint8_t
	{
		//Requests
		GetApp,
		GetDataBlock,

		//Response
		AppInfo,
		DataBlock,
	};

	struct MessageHeader
	{
		uint16_t Length;
		MessageType Type;
		uint8_t Reserved;
	};

	struct GetAppMessage : public MessageHeader
	{
		
	};

	struct GetDataBlockMessage : public MessageHeader
	{
		uint16_t BlockNumber;
		uint16_t Reserved;
	};

	struct AppInfoMessage : public MessageHeader
	{
		uint16_t NumberOfBlocks;
		uint16_t Reserved;
	};

	struct DataBlockMessage : public MessageHeader
	{
		uint16_t BlockNumber;
		uint16_t Reserved;
		uint8_t Data[DataSize];
	};
	static_assert(sizeof(DataBlockMessage) == 520, "Keeping this 512");
}
