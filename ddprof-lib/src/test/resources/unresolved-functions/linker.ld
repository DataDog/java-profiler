SECTIONS
{
    . = 0x10000;
    .text : { *(.text) }
    . = 0x20000;
    .data : { *(.data) }
    .bss : { *(.bss) }
    . = 0x30000;
    unresolved_symbol = .;
    . = 0xffffffffffffffff;
    unresolved_function = .;

}
