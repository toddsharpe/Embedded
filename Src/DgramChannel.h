#pragma once

#include "Callback.h"
#include "OutputChannel.h"
#include "Rtos/Types.h"

#include <cstdint>
#include <cstddef>

//Async dgram channel
class DgramChannel : public OutputChannel
{
public:
	DgramChannel() : DgramReceived() {};

	virtual ReadOnlyBuffer Read() = 0;
	Callback DgramReceived;
};
