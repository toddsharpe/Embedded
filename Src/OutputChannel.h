#pragma once

#include "Callback.h"
#include "Rtos/Types.h"

#include <cstdint>
#include <cstddef>

class OutputChannel
{
public:
	virtual void Write(const ReadOnlyBuffer& buffer) = 0;
};
