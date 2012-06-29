/*
 * bioscall.c
 *
 * Copyright (C) 2012 Simple Object Kernel
 * by Damien Dejean <djod4556@yahoo.fr>
 * Copyright (C) 2000 Simon Nieuviarts
 *
 * This module does BIOS calls in real mode.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

	.text
	.global bioscall

bioscall:
	/* Save function parameters */
	movl	4(%esp),%ecx
	movl	8(%esp),%edx

    /* Save flags and clear interruptions */
	pushfl
	cli

	/* Save the kernel IDT and GDT and segment registers. */
	sgdt	gdt_backup
	sidt	idt_backup
	pushw	%ds
	pushw	%es
	pushw	%fs
	pushw	%gs
	pushw	%ss

    /* Setup new data segment registers */
    movl    $0x10,  %eax
    movw    %ax,    %ds
    movw    %ax,    %es
    movw    %ax,    %fs
    movw    %ax,    %gs
    movw    %ax,    %ss

    /* Segments and interrupts stuff are saved, adjust pointers. */
    movl    $0xC0000000,    %eax
    subl    %eax,           %esp
    subl    %eax,           %ebp
    subl    %eax,           %ecx

    /* Call with right adressing mode */
    jmp     $0x08,  $real_code - 0xC0000000


/*
 * There is no more address translation, all pointers have to be physically
 * related to memory.
 */
real_code:
    /* Call real realmode code */
	pushl	%edx
	pushl	%ecx
    movl    $0x2000,%eax
	call	*(%eax)
	addl	$8,     %esp

	/* Restore the kernel IDT and GDT and segment registers. */
	lidt	idt_backup - 0xC0000000
	lgdt	gdt_backup - 0xC0000000
    jmp     $0x18,      $virtual_code


/*
 * Adresse are virtual again.
 */
virtual_code:
    /* Restore pointers */
    movl    $0xC0000000,    %eax
    addl    %eax,           %esp
    addl    %eax,           %ebp

    /* Return to translated memory to 3GB */
    movl    $0x20,  %eax
    movw    %ax,    %ds
    movw    %ax,    %es
    movw    %ax,    %fs
    movw    %ax,    %gs
    movw    %ax,    %ss

    /* Restore execution context */
	popw	%ss
	popw	%gs
	popw	%fs
	popw	%es
	popw	%ds
	popfl
	ret


/**
 * Some space to save current GDT and IDT descriptors.
 */
	.data
	.align  2
idt_backup:
	.word   0
	.long   0

	.align  2
gdt_backup:
	.word   0
	.long   0

