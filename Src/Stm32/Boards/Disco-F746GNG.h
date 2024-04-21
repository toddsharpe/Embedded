#pragma once

#include "Board.h"
#include "Stm32/GpioPin.h"
#include "Stm32/Ltdc.h"
#include "Stm32/Usart.h"

#include <cstdint>
#include <cstdarg>
#include <string>

namespace Board
{
	extern Stm32::Usart uart;
	extern Stm32::Ltdc ltdc;
	extern Stm32::GpioPin lcdInt;
	static constexpr size_t DisplayWidth = 480;
	static constexpr size_t DisplayHeight = 272;
}
