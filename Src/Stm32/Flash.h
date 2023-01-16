#pragma once

#include <stm32f746xx.h>
#include <cstdint>
#include <cstddef>

namespace Stm32
{
	class Flash
	{
	public:
		static void Unlock();
		static void Lock();

		static void EraseSector(const uint32_t sector);
		static void WriteByte(const uintptr_t address, const uint8_t data);
		static void WriteWord(const uintptr_t address, const uint32_t data);

	private:
		static constexpr uint32_t FLASH_KEY1 = 0x45670123U;
		static constexpr uint32_t FLASH_KEY2 = 0xCDEF89ABU;
		static constexpr uint32_t FLASH_OPT_KEY1 = 0x08192A3BU;
		static constexpr uint32_t FLASH_OPT_KEY2 = 0x4C5D6E7FU;

		static constexpr size_t SectorCount = 8;

		enum PSize
		{
			x8 = 0,
			x16 = FLASH_CR_PSIZE_0,
			x32 = FLASH_CR_PSIZE_1,
			x64 = FLASH_CR_PSIZE,
		};

		static void BusyWait();
	};
}
