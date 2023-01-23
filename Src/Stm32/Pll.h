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

	enum PllSaiDivR
	{
		DivR2 = 0b00,
		DivR4 = 0b01,
		DivR8 = 0b10,
		DivR16 = 0b11,
	};

	struct PllConfig
	{
		PllSrc Source;
		uint32_t M;
		uint32_t N;
		PllDiv P;
		uint32_t Q;
	};

	struct PllSaiConfig
	{
		uint32_t N;
		PllDiv P;
		uint32_t Q;
		uint32_t QDiv;
		uint32_t R;
		PllSaiDivR RDiv;
	};

	class Pll
	{
	public:
		static void Init(const PllConfig& config);
		static void Init(const PllSaiConfig& config);
	};
}

