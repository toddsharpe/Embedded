#
#!/bin/bash
#

export PATH=$PATH:/opt/STM32Cube/STM32CubeProgrammer/bin

# Test connection
STM32_Programmer_CLI -c port=JLINK

# Erasing
STM32_Programmer_CLI -c port=JLINK -e all

# Flash App
STM32_Programmer_CLI -c port=JLINK -w build/Stm32/Drone/Drone.bin 0x08000000 -v

STM32_Programmer_CLI -c port=JLINK -s
