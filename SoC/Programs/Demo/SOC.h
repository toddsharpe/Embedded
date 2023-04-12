#pragma once

#include <stdint.h>
#include <stddef.h>

#define __IO volatile
struct io_block
{
    __IO uint16_t led_display;
    uint16_t : 16;
    __IO uint16_t led_bar;
    uint16_t : 16;
    __IO uint16_t switches;
};

struct uart_block
{
    union
    {
        /*!< Transmit Data Register */
        struct
        {
            __IO uint32_t data : 8; /*!< Transmit Data */
            uint32_t : 23;
            __IO uint32_t full : 1; /*!< Transmit FIFO Full */
        } txdata;
    };
};

#define IO_BLOCK ((volatile struct io_block*)0x4000)
#define UART ((volatile struct uart_block*)0x4010)