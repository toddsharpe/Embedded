#pragma once

#include "stm32f746xx.h"
#include <cstddef>
#include <cstdint>

typedef void (*AppMain)(void);

/*
 * Flash memory organization, RM0385, Table 3.
 * Sector 0: 0x0800_0000-0x0800_7FFF, 32 Kbytes
 * Sector 1: 0x0800_8000-0x0800_FFFF, 32 Kbytes
 * Sector 2: 0x0801_0000-0x0801_7FFF, 32 Kbytes
 * Sector 3: 0x0801_8000-0x0801_FFFF, 32 Kbytes
 * Sector 4: 0x0802_0000-0x0803_FFFF, 128 Kbytes
 * Sector 5: 0x0804_0000-0x0807_FFFF, 256 Kbytes
 * Sector 6: 0x0808_0000-0x080B_FFFF, 256 Kbytes
 * Sector 7: 0x080C_0000-0x080F_FFFF, 256 Kbytes
 */
static constexpr uintptr_t Sector0 = FLASH_BASE;
static constexpr uintptr_t Sector2 = FLASH_BASE + 0x00010000U;
static constexpr uintptr_t Sector4 = FLASH_BASE + 0x00020000U;
static constexpr uintptr_t Sector5 = FLASH_BASE + 0x00040000U;
static constexpr uintptr_t Sector6 = FLASH_BASE + 0x00080000U;
static constexpr uintptr_t FlashEnd = FLASH_BASE + 0x000FFFFFU;

/*
 * Partition Addresses.
 */
namespace Addresses
{
	static constexpr uintptr_t BootRom = Sector0;
	static constexpr uintptr_t Boot0 = Sector2;
	static constexpr uintptr_t Boot1 = Sector4;
	static constexpr uintptr_t Boot2 = Sector5;
	static constexpr uintptr_t App = Sector6;
}

/*
 * Partition sectors.
 */
namespace Sectors
{
	static constexpr size_t Boot0_0 = 2;
	static constexpr size_t Boot0_1 = 3;
	static constexpr size_t Boot1 = 4;
	static constexpr size_t Boot2 = 5;
	static constexpr size_t App1 = 6;
}

/*
 * Bootrom: 64Kb
 * Bootloader: 64Kb
 * App: 512Kb
 */
static constexpr size_t BootRomSize = 64 * 1024;
static constexpr size_t BootloaderSize = 64 * 1024;
static constexpr size_t AppSize = 512 * 1024;
