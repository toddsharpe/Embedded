#
#!/bin/bash
#

export PATH=$PATH:/opt/STM32Cube/STM32CubeProgrammer/bin

STM32_Programmer_CLI -c port=SWD -hardRst
