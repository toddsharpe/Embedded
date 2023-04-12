# Create directories
SOC_DIR=../../../build/SoC
OUTPUT_DIR=$SOC_DIR/count
FPGA_MEM_FILE=$SOC_DIR/fpga.mem
rm -rf $OUTPUT_DIR
mkdir -p $OUTPUT_DIR

# Use SiFive toolchain
export TOOLCHAIN_PATH=/opt/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin

GCC=$TOOLCHAIN_PATH/riscv64-unknown-elf-gcc
LD=$TOOLCHAIN_PATH/riscv64-unknown-elf-ld
OBJCOPY=$TOOLCHAIN_PATH/riscv64-unknown-elf-objcopy
OBJDUMP=$TOOLCHAIN_PATH/riscv64-unknown-elf-objdump
AS=$TOOLCHAIN_PATH/riscv64-unknown-elf-as

# Build ELF (no c, no compression)
$AS count.S -o $OUTPUT_DIR/count.o -march=rv32ima -mabi=ilp32
$LD $OUTPUT_DIR/count.o -march=rv32imac -mabi=ilp32 -o $OUTPUT_DIR/count.elf -T count.ld -m elf32lriscv -nostdlib --no-relax

# Disassemble
$OBJDUMP -S --disassemble $OUTPUT_DIR/count.elf > $OUTPUT_DIR/count.disasm

# Hex and Bin
$OBJCOPY -O binary $OUTPUT_DIR/count.elf $OUTPUT_DIR/count.bin
hexdump -v -e '"%08x\n"' $OUTPUT_DIR/count.bin > $FPGA_MEM_FILE