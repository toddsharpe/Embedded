#
#!/bin/bash
#

set -e

$ObjCopy -O binary -S $BinFile.elf $BinFile.bin
$ObjCopy -O ihex $BinFile.elf $BinFile.hex
$ObjDump -S --disassemble $BinFile.elf > $BinFile.disasm
$Stat $BinFile.bin
