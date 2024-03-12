#pragma once

#include "Board.h"
#include "HiFive/Uart.h"
#include "HiFive/GpioPin.h"

namespace Board
{
	//Peripherals
	extern HiFive::Uart uart;
	extern HiFive::GpioPin LedRed;
	extern HiFive::GpioPin LedGreen;
	extern HiFive::GpioPin LedBlue;
}
