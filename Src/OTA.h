#pragma once

#include <stdint.h>
#include "Net/Net.h"

//Client: Get App
//Server: App size, # of blocks

//Client: Get block #
//Server: Data block#

namespace OTA
{
	static constexpr size_t DataSize = 1024;
	static const Net::IpAddress Server = { 172, 26, 1, 1};
	static constexpr uint16_t Port = 8080;
	
	enum MessageType : uint8_t
	{
		//Requests
		GetApp,
		GetDataBlock,

		//Response
		AppInfo,
		DataBlock,
	};

	struct __attribute__((packed)) MessageHeader
	{
		uint16_t Length;
		MessageType Type;
		uint8_t Reserved;
	};

	struct __attribute__((packed)) GetAppMessage : public MessageHeader
	{
		
	};

	struct __attribute__((packed)) GetDataBlockMessage : public MessageHeader
	{
		uint16_t BlockNumber;
		uint16_t Reserved;
	};

	struct __attribute__((packed)) AppInfoMessage : public MessageHeader
	{
		uint16_t NumberOfBlocks;
		uint16_t Reserved;
	};

	struct __attribute__((packed)) DataBlockMessage : public MessageHeader
	{
		uint16_t BlockNumber;
		uint16_t Reserved;
		uint8_t Data[DataSize];
	};
}
