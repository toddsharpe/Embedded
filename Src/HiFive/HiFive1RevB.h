#pragma once

#include "Board.h"
#include "HiFive/Uart.h"
#include "HiFive/GpioPin.h"
#include "HiFive/Prci.h"

namespace HiFive
{
	class HiFive1RevB : public Board
	{
	public:
		HiFive1RevB();

		void Init();

		virtual void Write(const std::string &str) override;
		virtual uint32_t GetSysClkFreq() const override;

		//Peripherals
		Uart uart;
		GpioPin<22> LedRed;
		GpioPin<19> LedGreen;
		GpioPin<21> LedBlue;
	};
}
