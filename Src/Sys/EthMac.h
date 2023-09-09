#pragma once

#include "Net/Net.h"
#include "Rtos/Types.h"
#include "Callback.h"

#include <cstddef>
#include <cstdint>

namespace Sys
{
	class EthMac
	{
	public:
		EthMac() :
			FrameReceived()
		{

		}

		virtual void Send(uint8_t* buffer, const size_t length) = 0;
		virtual void Display() = 0;

		ParamCallback<const Buffer&> FrameReceived;
	};
}
