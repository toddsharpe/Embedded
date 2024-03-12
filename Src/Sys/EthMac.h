#pragma once

#include "Buffer.h"
#include "Callback.h"

#include <cstddef>
#include <cstdint>

namespace EthMac
{
	void Init();
	void Send(const ReadOnlyBuffer& frame);
	void Display();
	void OnInterrupt(void* arg);

	static constexpr size_t BufferCount = 4;
	static constexpr size_t BufferSize = 1518;

	extern ParamCallback<const ReadOnlyBuffer&> FrameReceived;
}
