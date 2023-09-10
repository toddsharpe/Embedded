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

		virtual void Send(const ReadOnlyBuffer& frame) = 0;
		virtual void Display() = 0;

		ParamCallback<const ReadOnlyBuffer&> FrameReceived;
	};
}
