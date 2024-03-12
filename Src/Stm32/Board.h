#pragma once

#include <Board.h>
#include <cstdint>
#include <string>

namespace Board
{
	void Init();
	uint32_t GetSysClkFreq();
	void Write(const void* const buffer);
	void PrintBytes(const char* buffer, const size_t length);
}
