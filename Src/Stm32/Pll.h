#pragma once

#include "Assert.h"

#include <stm32f746xx.h>
#include <stm32f7xx.h>
#include <cstdint>

namespace Stm32
{
	enum PllSrc
	{
		HSI = 0,
		HSE = 1,
	};

	enum PllDiv
	{
		Div2 = 0b00,
		Div4 = 0b01,
		Div6 = 0b10,
		Div8 = 0b11,
	};

	struct PllConfig
	{
		PllSrc Source;
		uint32_t M;
		uint32_t N;
		PllDiv P;
		uint32_t Q;
	};

	struct RCC_PLLCFGR
	{
		union
		{
			struct
			{
				uint32_t PLLM : 6;
				uint32_t PLLN : 9;
				uint32_t _reserved1 : 1;
				uint32_t PLLP : 2;
				uint32_t _reserved2 : 4;
				uint32_t PLLSRC : 1;
				uint32_t _reserved3 : 1;
				uint32_t PLLQ : 4;
				uint32_t _reserved4 : 4;
			};
			uint32_t AsUint32;
		};
	};
	static_assert(sizeof(RCC_PLLCFGR) == sizeof(uint32_t));

	static constexpr PllConfig const DefaultPllConfig = { .Source = PllSrc::HSE, .M = 4, .N = 72, .P = PllDiv::Div2, .Q = 3 };

	class Pll
	{
	public:
		static void Init(const PllConfig& config);
	};
}

