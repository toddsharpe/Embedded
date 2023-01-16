#pragma once

#include "stm32f746xx.h"

typedef void (*AppMain)(void);

enum SystemMemoryMap
{
	Bootloader = FLASH_BASE,
	App = FLASH_BASE + 0x00040000U,
	SysReserved = FLASH_BASE + 0x000C0000U
};

enum SystemSectors
{
	App1 = 5,
	App2 = 6
};
