#
#!/bin/bash
#

set -e

$ObjCopy -O binary -S $BinFile.elf $BinFile.bin
$ObjCopy -O ihex $BinFile.elf $BinFile.hex
$ObjDump -S --disassemble $BinFile.elf > $BinFile.disasm
stat $BinFile.bin
hexdump -v -e '"%08x\n"' $BinFile.bin > $OutDir/fpga.mem
