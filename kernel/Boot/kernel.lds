/*
 * Simple Object Kernel
 * LD script to manage kernel location into memory.
 *
 * Copyright 2012-2013 by Damien Dejean <dam.dejean@gmail.com>
 */

ENTRY(entry);

SECTIONS
{
    /* Begining of the kernel at 1MB */
    . = 0x100000;
    _start = .;

    .text ALIGN(0x1000) : {
        *crt0.o(.text)
        *(.text)
        *(.gnu.linkonce.t*)
    }

    .realmodecode : {
        /* Real mode code */
        _real_mode_start = .;
        *(.realmodecode)
        _real_mode_end = .;
    }

    .rodata ALIGN(0x1000) : {

        /* C++ constructors list */
        _ctors_start = .;
        *(.ctor)
        _ctors_end = .;


        /* C++ destructors list */
        _dtors_start = .;
        *(.dtor)
        _dtors_end = .;

        *(.rodata*)
        *(.gnu.linkonce.r*)
    }

    .data ALIGN(0x1000) : {
        _data_start = .;
        *(.data)
        *(.gun.linkonce.d*)
        _data_end = .;
    }

    .bss : {
        _bss_start = .;
        *(.bss)
        *(COMMON)
        _bss_end = .;
    }
    _kernel_end = .;
}
