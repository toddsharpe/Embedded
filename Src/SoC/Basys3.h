#pragma once

#include "Board.h"

#include "SoC/Uart.h"

#include <cstdint>
#include <cstdarg>
#include <string>

namespace SoC
{
	class Basys3 : public Board
	{
	public:
		Basys3();

		void Init();

		virtual void Printf(const char *format, ...) override;
		virtual void Printf(const char *format, va_list args) override;
		virtual void Write(const std::string &str) override;
		virtual uint32_t GetSysClkFreq() const override;

		//Peripherals
		Uart uart;
	};
}