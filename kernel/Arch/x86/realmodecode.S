/*******************************************************************************
rmcode.S

Copyright (C) 2000 Simon Nieuviarts

This code is used to do BIOS calls.

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
#define ADR(x) (x-do_bios_call_rm+0x2000)
#define REGS_LEN (9*4+5*2)
#define REGS_EAX 0
#define REGS_EBX 4
#define REGS_ECX 8
#define REGS_EDX 12
#define REGS_ESI 16
#define REGS_EDI 20
#define REGS_EBP 24
#define REGS_ESP 28
#define REGS_EFLAGS 32
#define REGS_DS  36
#define REGS_ES  38
#define REGS_FS  40
#define REGS_GS  42
#define REGS_SS  44

	.text
/*******************************************************************************
void do_bios_call( bios_regs *regs, unsigned char int_no )
This is the single function of the module. It must be called in 32-bit protected
mode, without paging, and with CS, DS, ES and SS pointing to 32-bit segments
starting at 0.
On exit, the IDTR and the GDTR are left in an invalid state. The segment
registers point to 32-bit segments with an offset of 0 and a limit of
0xffffffff. The general registers are unchanged. Interrupts are disabled.
*******************************************************************************/
	.global do_bios_call_rm
do_bios_call_rm:
	.code32

	/* Interrupts are disabled. */
	cli

	/* Save the registers on the stack. */
	pushfl
	pushal

	/* Save the cr0 and cr3 register. */
	movl	%cr0,%eax
	pushl	%eax
	andl	$0x7fffffff,%eax
	movl	%eax,%cr0
	movl	%cr3,%eax
	pushl	%eax
	xorl	%eax,%eax
	movl	%eax,%cr3

	/* Load the GDTR to use our table. */
	lgdt	ADR(lgdt_val)

	/* Copy the interrupt vector of the interrupt we want to use to the
	vector 0xF1 (a user reserved vector). */
	movzbl	52(%esp),%eax	/* Skip cr0, cr3, pushal, pushf... */
	movl	(,%eax,4),%eax
	movl	%eax,0xF1*4

	movl	%esp,ADR(esp_saved)	/* Save the stack pointer. */
	movl	48(%esp),%esi		/* esi points to the regs buffer. */

	/* Copy the regs buffer to our buffer. */
	movl	$ADR(buffer),%edi
	movl	$REGS_LEN,%ecx
	cld
	rep
	movsb
	subl	$REGS_LEN,%esi

	movl	$0x20,%eax
	movl	%eax,%ds
	/* We can no more use the 32-bit datas. */

	/* Now, we can load the CS register. */
	ljmp	$0x18,$ADR(1f)
1:
	.code16
	movl	%cr0,%esi
	andl 	$0xfffffffe,%esi
	movl	%esi,%cr0
	ljmp	$0,$ADR(2f)
2:	/* We are now in the real mode. */

	/* Load the IDTR. */
	lidt	ADR(lidt_val)

	/* Load the stack pointer. */
	movw	ADR(buffer+REGS_SS),%ax
	movl	ADR(buffer+REGS_ESP),%edx
	movw	%ax,%ss
	movl	%edx,%esp

	/* Load the low part of the eflags register. */
	xorl	%eax,%eax
	movb	ADR(buffer+REGS_EFLAGS),%al
	pushl	%eax
	popfl

	/* Load the other general registers. */
	movl	ADR(buffer+REGS_EAX),%eax
	movl	ADR(buffer+REGS_EBX),%ebx
	movl	ADR(buffer+REGS_ECX),%ecx
	movl	ADR(buffer+REGS_EDX),%edx
	movl	ADR(buffer+REGS_ESI),%esi
	movl	ADR(buffer+REGS_EDI),%edi
	movl	ADR(buffer+REGS_EBP),%ebp

	/* Push the data segment registers on the stack. */
	pushw	ADR(buffer+REGS_DS)
	pushw	ADR(buffer+REGS_ES)
	pushw	ADR(buffer+REGS_FS)
	pushw	ADR(buffer+REGS_GS)

	/* Load the data segment registers. */
	popw	%gs
	popw	%fs
	popw	%es
	popw	%ds

	/* Execute the interrupt. */
	int	$0xF1

	/* Save EFLAGS on the stack. */
	pushfl

	/* Save the segment registers on the stack. */
	pushw	%ds
	pushw	%es
	pushw	%fs
	pushw	%gs

	/* Save the registers in our buffer. */
	pushw	%ax
	xorw	%ax,%ax
	movw	%ax,%ds
	popw	%ax
	popw	ADR(buffer+REGS_GS)
	popw	ADR(buffer+REGS_FS)
	popw	ADR(buffer+REGS_ES)
	popw	ADR(buffer+REGS_DS)
	popl	ADR(buffer+REGS_EFLAGS)
	movl	%eax,ADR(buffer+REGS_EAX)
	movl	%ebx,ADR(buffer+REGS_EBX)
	movl	%ecx,ADR(buffer+REGS_ECX)
	movl	%edx,ADR(buffer+REGS_EDX)
	movl	%esi,ADR(buffer+REGS_ESI)
	movl	%edi,ADR(buffer+REGS_EDI)
	movl	%esp,ADR(buffer+REGS_ESP)
	movl	%ebp,ADR(buffer+REGS_EBP)

	/* All registers are saved. Return to the protected mode. */
	cli
	movw	$0x0010,%cx
	movl	%cr0,%eax
	orl	$1,%eax
	movl	%eax,%cr0
	ljmp	$0x8,$ADR(3f)
3:
	.code32
	movl	%ecx,%ds
	movl	%ecx,%es
	movl	%ecx,%fs
	movl	%ecx,%gs
	movl	%ecx,%ss
	movl	ADR(esp_saved),%esp

	/* Copy our buffer to the regs buffer. */
	movl	48(%esp),%edi
	movl	$ADR(buffer),%esi
	movl	$REGS_LEN,%ecx
	cld
	rep
	movsb

	/* Restore the cr0 and cr3 register. */
	popl	%eax
	movl	%eax,%cr3
	popl	%eax
	movl	%eax,%cr0

	popal
	popfl
	retl

	.align  2
	/* Location of the real mode IDT. */
lidt_val:
	.word   1023
	.long   0

	.align  2
lgdt_val:
	.word   5 * 8 - 1
	.long   ADR(loader_gdt)

	.align  4
/* The GDT to switch to protected mode. */
loader_gdt:
/* 0: Null descriptor. */
	.long	0, 0

/* 1: A system code segment : 32-bit, 4G, base=0, CPL=0. */
	.byte	0xFF, 0xFF, 0, 0, 0, 0x9B, 0xCF, 0

/* 2: A system data segment : 4G, base=0, DPL=0. Also used for the stack. */
	.byte	0xFF, 0xFF, 0, 0, 0, 0x93, 0xCF, 0

/* 3: A code segment for the real mode : 16 bits, 64K, base=0, CPL=0. */
	.byte	0xFF, 0xFF, 0, 0, 0, 0x9B, 0x00, 0

/* 4: A data segment for the real mode : 16 bits, 64K, base=0, CPL=0. */
	.byte	0xFF, 0xFF, 0, 0, 0, 0x93, 0x00, 0

	.align  4
esp_saved:
	.long	0
buffer:
	.zero	REGS_LEN

