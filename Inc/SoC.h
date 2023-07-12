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

struct spi_dma_block
{
    /*!< Config Register */
    struct
    {
        __IO uint32_t start : 1; /*!< Start DMA transfer */
        __IO uint32_t dir : 1;   /*!< 0: Peripheral to memory, 1: Memory to peripheral */
        __IO uint32_t size : 2;  /*!< 0: 8-bit, 1: 16-bit, 2: 32-bit */
        uint32_t : 27;           /*!< Reserved */
        __IO uint32_t busy : 1; /*!< DMA in progress */
    } config;
    __IO uint32_t count;
    __IO uint32_t periph_addr;
    __IO uint32_t mem_addr;
};

#define DEVICE_START 0x100000
#define SOC_BLOCK ((struct soc_block*)(DEVICE_START + 0x000))
#define IO_BLOCK ((struct io_block*)(DEVICE_START + 0x100))
#define GPIO1 ((struct gpio_block*)(DEVICE_START + 0x200))
#define UART ((struct uart_block*)(DEVICE_START + 0x300))
#define SPI1 ((struct spi_block*)(DEVICE_START + 0x400))
#define SPI_DMA1 ((struct spi_dma_block*)(DEVICE_START + 0x500))
