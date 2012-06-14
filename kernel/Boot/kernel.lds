/*
 * Simple Object Kernel
 * LD script to manage kernel location into memory.
 *
 * Copyright 2012 by Damien Dejean <djod4556@yahoo.fr>
 */

/* Higher-half kernel */
kernel_offset = 0xC0000000;

SECTIONS
{
    /* Begining of the kernel */
    . = 0x100000 + kernel_offset;
    _start = .;

    .text ALIGN(0x1000): AT(ADDR(.text) - kernel_offset) {
        */crt0.o(.text)
        *(.text)
        *(.gnu.linkonce.t*)
    }

    .realmodecode : AT(ADDR(.realmodecode) - kernel_offset) {
        /* Real mode code */
        _real_mode_start = .;
        *(.realmodecode)
        _real_mode_end = .;
    }

    .rodata ALIGN(0x1000): AT(ADDR(.rodata) - kernel_offset) { 

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

    .data ALIGN(0x1000): AT(ADDR(.data) - kernel_offset) {
        _data_start = .;
        *(.data)
        *(.gun.linkonce.d*)
        _data_end = .;
    }

    .bss : AT(ADDR(.bss) - kernel_offset) {
        _bss_start = .;
        *(.bss)
        *(COMMON)
        _bss_end = .;
    }
}
