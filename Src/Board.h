#pragma once

#include <cstdarg>
#include "StringPrinter.h"

class Board : public StringPrinter
{
public:
	virtual void Printf(const char *format, ...) = 0;
	virtual void Printf(const char* format, va_list args) = 0;
	virtual void Write(const std::string& str) = 0;

	virtual uint32_t GetSysClkFreq() const = 0;
};