ENTRY(_enter)

MEMORY
{
   BRAM (RWX) : ORIGIN = 0x0000, LENGTH = 0x4000
}

SECTIONS
{
    __stack_size = DEFINED(__stack_size) ? __stack_size : 0x400;
    PROVIDE(__stack_size = __stack_size);

    __heap_size = DEFINED(__heap_size) ? __heap_size : 0x800;

    .text : {
        . = ALIGN(4);
        *(.text.init.enter*)
        *(.text .text.*)
    } >BRAM

    .rodata :
    {
        *(.rdata)
        *(.rodata .rodata.*)
        . = ALIGN(4);
    } >BRAM

    .data : ALIGN(8)
    {
        *(.data .data.*)
        . = ALIGN(8);
        PROVIDE( __global_pointer$ = . + 0x800 );
        *(.sdata .sdata.* .sdata2.*)
    } >BRAM

    /* Uninitialized data section into "RAM" Ram type memory */
    . = ALIGN(4);
    .bss :
    {
        /* This is used by the startup in order to initialize the .bss section */
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
    } >BRAM

    .stack (NOLOAD) : ALIGN(16) {
        PROVIDE(_stack_begin = .);
        . += __stack_size;
        PROVIDE( _sp = . );
        PROVIDE(_stack_end = .);
    } >BRAM

    .heap (NOLOAD) : ALIGN(8) {
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        PROVIDE( __end = . );
        PROVIDE( __heap_start = . );
        . = DEFINED(__heap_max) ? (LENGTH(BRAM) - (. - ORIGIN(BRAM))) : __heap_size;
        PROVIDE( _heap_end = . );
        PROVIDE( __heap_end = . );
    } >BRAM

    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
}
