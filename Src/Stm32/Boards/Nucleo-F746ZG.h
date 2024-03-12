#pragma once

#include "Board.h"
#include "Stm32/Usart.h"
#include "Stm32/GpioPin.h"

namespace Board
{
	extern Stm32::Usart uart;
	extern Stm32::GpioPin Led1;
	extern Stm32::GpioPin Led2;
	extern Stm32::GpioPin Led3;
}
