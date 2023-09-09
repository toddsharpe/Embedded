export PATH=$PATH:/opt/STM32Cube/STM32CubeProgrammer/bin

# Test connection
STM32_Programmer_CLI -c port=SWD

# Erasing
STM32_Programmer_CLI -c port=SWD -e all

# Flashing Bootloader
STM32_Programmer_CLI -c port=SWD -w build/Stm32/Bootloader/Bootloader.bin 0x08000000 -v

# Flashing App
STM32_Programmer_CLI -c port=SWD -w build/Stm32/App/Nucleo.bin 0x08040000 -v

STM32_Programmer_CLI -c port=SWD -s
