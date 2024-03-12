#pragma once

#include "Buffer.h"
#include <cstdarg>

namespace Board
{
	void Init();
	void Printf(const char* format, ...);
	void PrintfVA(const char* format, va_list args);
	void PrintBytes(const char* buffer, const size_t length);
	void Write(const ReadOnlyBuffer& buffer);
	uint32_t GetSysClkFreq();
};
