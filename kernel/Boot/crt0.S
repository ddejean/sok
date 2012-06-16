/*
 * Copyright (C) 2012, the Simple Object Kernel project.
 *
 * crt0.s Assembly bootstrap for x86 targets
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * This kernel entry point expect to be loaded by a multiboot compliant
 * bootloader like GRUB.
 *
 * Requirements:
 * - Set up a virtual address space to allow the kernel to use 3 GB based
 *   virtual addresses
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
    .long    multiboot_header - 0xC0000000       /* Multiboot structure adress */
    .long    _start - 0xC0000000                 /* Start of kernel binary in memory */
    .long    _data_end - 0xC0000000              /* End of data to load */
    .long    _bss_end - 0xC0000000               /* End of BSS section, erased by loader */
    .long    entry - 0xC0000000                  /* Address of the kernel entry point */

/*
 * Entry point of the kernel
 */
.global entry
entry:
    /* Ensure interrupts are disabled in bootstrap process */
    cli

    /* Save multiboot informations */
    movl    %eax,           multiboot_magic - 0xC0000000
    addl    $0xC0000000,    %ebx
    movl    %ebx,           multiboot_info - 0xC0000000

    /* Load the tricky GDT */
    lgdtl   gdt_desc - 0xC0000000
    movw    $0x20,      %ax
    movw    %ax,        %ds
    movw    %ax,        %es
    movw    %ax,        %fs
    movw    %ax,        %gs
    movw    %ax,        %ss
    jmp     $0x18,      $virtual_kernel

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
    .long   bootstrap_gdt - 0xC0000000

    .align  4
virtual_gdt_desc:
    .word   bootstrap_gdt_end - bootstrap_gdt - 1
    .long   bootstrap_gdt

    .align 4
bootstrap_gdt:
    .long   0x0         /* Null gate */
    .long   0x0
    .long   0x0000FFFF  /* Code selector without offset */
    .long   0x00CF9A00
    .long   0x0000FFFF  /* Data selector without offset */
    .long   0x00CF9200
    .long   0x0000FFFF  /* Code selector with offset 0x40000000 */
    .long   0x40CF9A00
    .long   0x0000FFFF  /* Data selector with offset 0x40000000 */
    .long   0x40CF9200
bootstrap_gdt_end:

    .align  4
first_stack:
    .fill   4096, 4, 0   /* Create a stack of 4096*4 bytes filled with 0s */
