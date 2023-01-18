#!/bin/bash

mkdir -p build/Stm32
mkdir -p build/HiFive

# Build STM binaries

echo "Building HelloDisco"
cd Src/Stm32/HelloDisco
make
cd ../../../

echo "Building STM32 App"
cd Src/Stm32/App
make
cd ../../../

echo "Building STM32 Bootloader"
cd Src/Stm32/Bootloader
make
cd ../../../

# Build SiFive binaries
export GCC_PATH=/opt/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin

echo "Building HiFive App"
cd Src/HiFive/App
make
cd ../../../