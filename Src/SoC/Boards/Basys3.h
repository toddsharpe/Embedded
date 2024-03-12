#pragma once

#include "Board.h"

#include "SoC/Uart.h"

#include <cstdint>
#include <cstdarg>
#include <string>

namespace Board
{
	//Peripherals
	extern SoC::Uart uart;
}
