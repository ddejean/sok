/*******************************************************************************
bioscall-wrapper.S

Copyright (C) 2000 Simon Nieuviarts

This code is the wrapping code of do_bios_call for our kernel.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*******************************************************************************/
	.text
/*******************************************************************************
void do_bios_call( bios_regs *regs, unsigned char int_no )
This is the single function of the module. It must be called in 32-bit protected
mode, without paging, and with CS, DS, ES and SS pointing to 32-bit segments
starting at 0.
The general registers are unchanged. Interrupts are disabled.
*******************************************************************************/
	.global do_bios_call
do_bios_call:
	testb	$0xff,init_done
	jnz	0f

	/* Copy the rmcode at 0x2000. */
	movb	$0x01,init_done
	pushl	%esi
	pushl	%edi
	leal	rmcode_end,%ecx
	leal	rmcode_start,%esi
	leal	0x2000,%edi
	subl	%esi,%ecx
	addl	$3,%ecx
	sarl	$2,%ecx
	cld
	rep
	movsl
	popl	%edi
	popl	%esi

0:	/* Real mode code copied at 0x2000. */
	movl	4(%esp),%ecx
	movl	8(%esp),%edx

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
	lcall	$0x10,$0f
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
	call	0x2000
	addl	$8,%esp

	/* Restore the kernel IDT and GDT and segment registers. */
	lidt	idt_loc
	lgdt	gdt_loc
	lret

	.data
init_done:
	.byte	0

	.align  2
	/* Location of the kernel IDT. */
idt_loc:
	.word   0
	.long   0

	.align  2
	/* Location of the kernel GDT. */
gdt_loc:
	.word   0
	.long   0

