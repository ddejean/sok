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

#ifndef __BIOSCALL_H__
#define __BIOSCALL_H__


#define REGX(a) ((a) & 0xffff)
#define REGL(a) ((a) & 0xff)
#define REGH(a) (((a) >> 8) & 0xff)


/**
 *  Intel x86 CPU registers structure.
 */
struct bios_regs {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int esi;
	unsigned int edi;
	unsigned int ebp;
	unsigned int esp;
	unsigned int eflags;
	unsigned short ds;
	unsigned short es;
	unsigned short fs;
	unsigned short gs;
	unsigned short ss;
};

/**
 * Perform a call to BIOS in realmode.
 * @param regs the CPU registers to set before the call. Will contain the state
 *        of the CPU after the call.
 * @param int_no the number of the bioscall/interrupt to perform.
 *
 * @note must be called in protected mode.
 */
void bioscall(struct bios_regs *regs, unsigned char int_no);


#endif

