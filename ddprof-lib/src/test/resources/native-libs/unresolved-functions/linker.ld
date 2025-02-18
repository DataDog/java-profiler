PHDRS
{
    headers PT_PHDR PHDRS ;
    interp PT_INTERP ;
    text PT_LOAD FILEHDR PHDRS ;
    data PT_LOAD ;
}

SECTIONS
{
    . = 0x10000;
    .text : {
        *(.text)
    } :text

    . = 0x20000;
    .data : {
        *(.data)
    } :data

    .bss : {
        *(.bss)
    }

    . = 0x30000;
    unresolved_symbol = .;
    . = 0xffffffffffffffff;
    unresolved_function = .;

    /* Add the .init_array section */
    .init_array : {
        __init_array_start = .;
        KEEP(*(.init_array))
        __init_array_end = .;
    }

    /* Add the .fini_array section */
    .fini_array : {
        __fini_array_start = .;
        KEEP(*(.fini_array))
        __fini_array_end = .;
    }
}
