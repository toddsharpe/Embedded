set CUBE_BIN=C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin

REM Erasing
"%CUBE_BIN%\STM32_Programmer_CLI.exe" -c port=SWD -e all

REM Flashing HelloDisco
"%CUBE_BIN%\STM32_Programmer_CLI.exe" -c port=SWD -w build\stm32\HelloDisco\Disco.bin 0x08000000 -v

"%CUBE_BIN%\STM32_Programmer_CLI.exe" -c port=SWD -s