#!/bin/bash

set -e

mkdir -p build/Stm32/HelloDisco
mkdir -p build/Stm32/App
mkdir -p build/Stm32/Bootloader
mkdir -p build/HiFive/App
mkdir -p build/SoC/Bootloader

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

# Build SoC Binaries
export GCC_PATH=/opt/riscv32-unknown-elf/bin

echo "Building SoC Bootloader"
cd Src/SoC/Bootloader
make
cd ../../../