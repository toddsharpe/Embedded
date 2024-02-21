#pragma once

#include <stdint.h>
#include <stddef.h>

#define __IO volatile

struct soc_block
{
    __IO uint32_t cycles;
    __IO uint32_t freq;
};

struct io_block
{
    __IO uint16_t led_display;
    uint16_t : 16;
    __IO uint16_t led_bar;
    uint16_t : 16;
    __IO uint16_t switches;
};

struct gpio_block
{
    __IO uint32_t data_in;
    __IO uint32_t data_out;
    __IO uint32_t dir;
};

struct uart_block
{
    /*!< Transmit Data Register */
    struct
    {
        __IO uint32_t data : 8; /*!< Transmit Data */
        uint32_t : 23;
        __IO uint32_t full : 1; /*!< Transmit FIFO Full */
    } txdata;
};

struct spi_block
{
    /*!< Transmit Data Register */
    struct
    {
        __IO uint32_t data : 8; /*!< Transmit Data */
        uint32_t : 23;
        __IO uint32_t full : 1; /*!< Transmit FIFO Full */
    } txdata;
};

#define DEVICE_START 0x100000
#define SOC_BLOCK ((struct soc_block*)(DEVICE_START + 0x000))
#define IO_BLOCK ((struct io_block*)(DEVICE_START + 0x100))
#define GPIO1 ((struct gpio_block*)(DEVICE_START + 0x200))
#define UART ((struct uart_block*)(DEVICE_START + 0x300))
#define SPI1 ((struct spi_block*)(DEVICE_START + 0x400))
