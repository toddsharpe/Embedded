#pragma once

#include <cstdint>

namespace Stm32
{
	struct RccClocks
	{
		uint32_t SysClkFreq;
		uint32_t HClkFreq;
		uint32_t PClk1Freq;
		uint32_t PClk1TimerFreq;
		uint32_t PClk2Freq;
	};

	class Rcc
	{
	public:
		Rcc(const uint32_t hsiFreq, const uint32_t hseFreq);

		void GetSystemClocksFreq(RccClocks &clocks) const;

		uint32_t GetSysClkFreq() const;
		uint32_t GetPClk1Freq() const;
		uint32_t GetPClk1TimerFreq() const;
		uint32_t GetPClk2Freq() const;
		uint32_t GetScaledClkFreq(const uint32_t sysClk, const uint32_t prescaler) const;
		uint32_t GetLcdFreq() const;

	private:
		static constexpr uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};

		const uint32_t m_hsiFreq;
		const uint32_t m_hseFreq;
	};
}
