#include "SOC.h"
#include <string.h>
#include "printf.h"

void write(const uint8_t *buffer, size_t length);

void _putchar(char character)
{
	while (UART->txdata.full) {};
	UART->txdata.data = character;
}

void main()
{
	printf("i %d\r\n", 123);

	uint32_t value = 0;
	while (1)
	{
		if (IO_BLOCK->switches & 0x1)
		{
			// Count down
			value--;
		}
		else
		{
			// Count up
			value++;
		}

		// Display
		IO_BLOCK->led_display = value;
		IO_BLOCK->led_bar = value;

		//Delay
		for (volatile int i = 0; i < 50000; i++)
			__asm("nop");
	}

	__asm("ebreak");
}

void write(const uint8_t *buffer, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		while (UART->txdata.full) {};
		UART->txdata.data = buffer[i];
	}
	while (UART->txdata.full) {};
}