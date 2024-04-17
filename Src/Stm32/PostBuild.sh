#
#!/bin/bash
#

set -e

$ObjCopy -O binary -S $BinFile.elf $BinFile.bin
$ObjCopy -O ihex $BinFile.elf $BinFile.hex
$ObjDump -S --disassemble $BinFile.elf > $BinFile.disasm
$ObjDump -s -j .isr_vector $BinFile.elf > $BinFile.isr_vector
$Stat $BinFile.bin
