#pragma once

#include "Board.h"

#include "Stm32/Rcc.h"
#include "Stm32/Usart.h"
#include "Stm32/GpioPin.h"

#include <cstdint>
#include <cstdarg>
#include <string>

namespace Stm32
{
	class NucleoF746ZG : public Board
	{
	public:
		NucleoF746ZG();

		void Init();

		virtual void Printf(const char *format, ...) override;
		virtual void Printf(const char *format, va_list args) override;
		virtual void Write(const std::string &str) override;
		virtual uint32_t GetSysClkFreq() const override;

		//Peripherals
		Rcc rcc;
		Usart uart;
		GpioPin<Port_B, 0> Led1;
		GpioPin<Port_B, 7> Led2;
		GpioPin<Port_B, 14> Led3;
	};
}
