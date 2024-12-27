#pragma once

#include "Board.h"
#include "Stm32/GpioPin.h"
#include "Stm32/Pwm.h"

//SPI1: BLUENRG-M0A
//SPI2: LPS22HH, LSM6DSR

namespace Board
{
	extern Stm32::GpioPin Led1;
	extern Stm32::GpioPin Led2;
	extern Stm32::Pwm motor_pwm;
}
