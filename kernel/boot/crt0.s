/*
 * crt0.s Assembly bootstrap for x86 targets
 *
 * Copyright 2012 by Damien Dejean <djod4556@yahoo.fr>
 * 
 * This kernel entry point expect to be loaded by a multiboot compliant
 * bootloader like GRUB.
 */

.text

/* Somewhere to store multiboot data */
.comm       multiboot_magic, 4, 4
.comm       multiboot_info,  4, 4

/* 
 * Multiboot header
 * @note: we need physical addresses.
 */
.p2align 2
multiboot_header:
    .long    0x1BADB002              /* Multiboot magic */
    .long    0x00010002              /* Multiboot flags: what we want to know from the loader */
    .long    -0x1BADB002-0x00010002  /* Checksum */
    .long    multiboot_header        /* Multiboot structure adress */
    .long    _start                  /* Start of kernel binary in memory */
    .long    _data_end               /* End of data to load */
    .long    _bss_end                /* End of BSS section, erased by loader */
    .long    entry                   /* Address of the kernel entry point */



/* Entry point of the kernel */
.global entry
entry:
    cli
    hlt

