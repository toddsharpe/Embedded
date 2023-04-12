# Create directories
SOC_DIR=../../../build/SoC
OUTPUT_DIR=$SOC_DIR/demo
FPGA_MEM_FILE=$SOC_DIR/fpga.mem
rm -rf $OUTPUT_DIR
mkdir -p $OUTPUT_DIR

# Use SoC toolchain
export TOOLCHAIN=/opt/rv32i/
export BIN_PATH=$TOOLCHAIN/bin
export LIB_PATH=$TOOLCHAIN/lib

GCC=$BIN_PATH/riscv32-unknown-elf-gcc
LD=$BIN_PATH/riscv32-unknown-elf-ld
OBJCOPY=$BIN_PATH/riscv32-unknown-elf-objcopy
OBJDUMP=$BIN_PATH/riscv32-unknown-elf-objdump
AS=$BIN_PATH/riscv32-unknown-elf-as

# Build ELF (no c, no compression)
$GCC -r -g demo.c -o $OUTPUT_DIR/demo.o -march=rv32ima -mabi=ilp32 -O0 -ffunction-sections
$GCC -r -g start.c -o $OUTPUT_DIR/start.o -march=rv32ima -mabi=ilp32 -O0 -ffunction-sections
$GCC $OUTPUT_DIR/demo.o $OUTPUT_DIR/start.o -march=rv32ima -mabi=ilp32 --specs=nano.specs -nostartfiles -o $OUTPUT_DIR/demo.elf -T demo.ld -Wl,--start-group -lc -lm -lstdc++ -lnosys  -Wl,--end-group -Wl,-Map=$OUTPUT_DIR/demo.map -mno-relax

# Disassemble
$OBJDUMP -S --disassemble $OUTPUT_DIR/demo.elf > $OUTPUT_DIR/demo.disasm

# Hex and Bin
$OBJCOPY -O binary $OUTPUT_DIR/demo.elf $OUTPUT_DIR/demo.bin
hexdump -v -e '"%08x\n"' $OUTPUT_DIR/demo.bin > $FPGA_MEM_FILE