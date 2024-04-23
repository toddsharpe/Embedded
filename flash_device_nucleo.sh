#
#!/bin/bash
#

export PATH=$PATH:/opt/STM32Cube/STM32CubeProgrammer/bin

# Test connection
STM32_Programmer_CLI -c port=SWD

# Erasing
STM32_Programmer_CLI -c port=SWD -e all

# Flash Bootrom
STM32_Programmer_CLI -c port=SWD -w build/Stm32/Bootrom/Bootrom.bin 0x08000000 -v

# Flashing Bootloader
STM32_Programmer_CLI -c port=SWD -w build/Stm32/Bootloader/Bootloader.bin 0x08010000 -v

# Flashing Nucleo
STM32_Programmer_CLI -c port=SWD -w build/Stm32/Nucleo/Nucleo.bin 0x08080000 -v

STM32_Programmer_CLI -c port=SWD -s
