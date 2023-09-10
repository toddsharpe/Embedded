#pragma once

#include <cstdarg>
#include "StringPrinter.h"

class Board : public StringPrinter
{
public:
	virtual uint32_t GetSysClkFreq() const = 0;
};
