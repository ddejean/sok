/*
 * Copyright (C) 2012-2013, the Simple Object Kernel project.
 *
 * crt0.S Assembly bootstrap for x86 targets
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * This kernel entry point expect to be loaded by a multiboot compliant
 * bootloader like GRUB.
 *
 * Requirements:
 * - Set up a primary stack
 * - The kernel must block in a fashion and power efficient way if the call
 *   to stage1_main returns.
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
    .long    0x1BADB002                          /* Multiboot magic */
    .long    0x00010003                          /* Multiboot flags: what we want to know from the loader */
    .long    -0x1BADB002-0x00010003              /* Checksum */
    .long    multiboot_header                    /* Multiboot structure adress */
    .long    _start                              /* Start of kernel binary in memory */
    .long    _data_end                           /* End of data to load */
    .long    _bss_end                            /* End of BSS section, erased by loader */
    .long    entry                               /* Address of the kernel entry point */

/*
 * Entry point of the kernel
 */
.global entry
entry:
    /* Ensure interrupts are disabled in bootstrap process */
    cli

    /* Save multiboot informations */
    movl    %eax,           multiboot_magic
    movl    %ebx,           multiboot_info

    /* Load the tricky GDT */
    lgdtl   gdt_desc
    movw    $0x10,      %ax
    movw    %ax,        %ds
    movw    %ax,        %es
    movw    %ax,        %fs
    movw    %ax,        %gs
    movw    %ax,        %ss
    jmp     $0x8,       $virtual_kernel

/*
 * Virtual kernel entry point.
 * Let the debugger align on new addresses translation
 */
virtual_kernel:
    /* Setup the stack */
    leal        first_stack,        %esp
    addl        $16384,             %esp
    xorl        %ebp,               %ebp

    /* Use it to clear flags (this let interrupt disabled) */
    pushl        $0
    popfl

    /* Prepare and call stage1 */
    pushl   multiboot_info
    pushl   multiboot_magic
    call    stage1_main
    addl    $8,                 %esp

    /* Kernel may never return, stay blocked here */
    cli
    hlt

/*
 * Global Descriptor Table to let the CPU use addresses with the kernel_offset
 * offset. This tricky GDT avoid to translate manually all addresses until a
 * page table is installed.
 */
    .align  4
gdt_desc:
    .word   bootstrap_gdt_end - bootstrap_gdt - 1
    .long   bootstrap_gdt

    .align 4
    .global bootstrap_gdt
bootstrap_gdt:
    .long   0x0         /* Null gate */
    .long   0x0
    .long   0x0000FFFF  /* Code selector without offset */
    .long   0x00CF9A00
    .long   0x0000FFFF  /* Data selector without offset */
    .long   0x00CF9200
    .global bootstrap_gdt_end
bootstrap_gdt_end:

    .align  4
first_stack:
    .fill   4096, 4, 0   /* Create a stack of 4096*4 bytes filled with 0s */
