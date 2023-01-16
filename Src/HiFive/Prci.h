#pragma once

#include "Assert.h"

#include <cstdint>
#include <FE310.h>

namespace HiFive
{
	struct PrciConfig
	{
		uint32_t R;
		uint32_t F;
		uint32_t Q;
		bool UsePll;
	};

	//Yields 320mhz clock (from 16mhz ref)
	static constexpr PrciConfig const DefaultPrciConfig = { .R = 2, .F = 80, .Q = 2, .UsePll = true };

	class Prci
	{
	public:
		//NOTE(tsharpe): pllcfg_b power-on value: 0x00070000. Sel, Refsel, Bypass
		static void Init(const PrciConfig& config)
		{
			//Ensure PLL is bypassed
			Assert(PRCI->pllcfg_b.bypass);

			//Set PLL config
			PRCI->pllcfg = 0;
			PRCI->pllcfg_b.sel = 0;
			PRCI->pllcfg_b.pllr = config.R - 1;
			PRCI->pllcfg_b.pllf = (config.F / 2 - 1);
			PRCI->pllcfg_b.pllq = config.Q - 1;
			PRCI->pllcfg_b.refsel = 1; //Select HFXOSC (16mhz)

			//Wait for PLL to be ready
			while (!PRCI->pllcfg_b.lock)
				continue;

			PRCI->pllcfg_b.sel = true;
		}

		static uint32_t GetSysClkFreq()
		{
			if (PRCI->pllcfg_b.bypass)
				return HFXOSC;

			Assert(PRCI->pllcfg_b.sel);
			Assert(PRCI->pllcfg_b.refsel);

			return HFXOSC / (PRCI->pllcfg_b.pllr + 1) * 2 * (PRCI->pllcfg_b.pllf + 1)  / (PRCI->pllcfg_b.pllq + 1);
		}

	private:
		static constexpr uint32_t HFXOSC = 16000000;
	};
}