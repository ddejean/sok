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
	sgdt	gdt_loc
	sidt	idt_loc
	pushw	%ds
	pushw	%es
	pushw	%fs
	pushw	%gs
	pushw	%ss
	lcall	$0x08,$0f
	popw	%ss
	popw	%gs
	popw	%fs
	popw	%es
	popw	%ds
	popfl
	ret

0:	/* Segments and interrupts stuff are saved. */
	pushl	%edx
	pushl	%ecx
	call	(0x2000 + 0xC0000000)
	addl	$8,%esp

	/* Restore the kernel IDT and GDT and segment registers. */
	lidt	idt_loc
	lgdt	gdt_loc
	lret

/**
 * Some space to save current GDT and IDT descriptors.
 */
	.data
	.align  2
idt_loc:
	.word   0
	.long   0

	.align  2
gdt_loc:
	.word   0
	.long   0

