MEMORY
{
   BRAM (RWX) : ORIGIN = 0x0000, LENGTH = 0x200  /* 512B RAM */
}
SECTIONS
{
    everything :
    {
    . = ALIGN(4);
    ../../../build/SoC/count/count.o (.text)
    } >BRAM
}
