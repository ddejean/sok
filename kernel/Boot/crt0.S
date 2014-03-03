/*
 * Copyright (C) 2012-2014, the Simple Object Kernel project.
 *
 * crt0.S Assembly bootstrap for x86 targets
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * This kernel entry point expect to be loaded by a multiboot compliant
 * bootloader like GRUB.
 *
 * Requirements:
 * - Set up a primary stack
 * - Setup an identity segmentation
 * - Prevent stage1_main buggy returns.
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

    /* Load a simple GDT */
    lgdtl   gdt_desc
    movw    $0x10,      %ax
    movw    %ax,        %ds
    movw    %ax,        %es
    movw    %ax,        %fs
    movw    %ax,        %gs
    movw    %ax,        %ss
    jmp     $0x8,       $kernel_with_segments

/*
 * Kernel entry point after identity segmentation.
 * Let the debugger align on new addresses translation
 */
kernel_with_segments:
    /* Setup the stack */
    leal        bootstrap_stack,    %esp
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
 * offset.
 * This is a simple bootstrap GDT to define basic segments for kernel boot.
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

/*
 * Special section for the first kernel stack. Allows to map code and rodata
 * regions to read only and boostrap stack to read/write.
 */
.section bootstrap_stack
    .align  4
boostrap_stack:
    .fill   4096, 4, 0   /* Create a stack of 4096*4 bytes filled with 0s */
