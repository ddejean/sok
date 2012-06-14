/*
 * cpu.h
 *
 * Copyright (C) 2010 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * CPU specific instructions and structures.
 */
#ifndef __CPU_H__
#define __CPU_H__

#include "stdint.h"

__inline__ static void outb(uint8_t value, uint16_t port)
{
	__asm__ __volatile__("outb %0, %1" : : "a" (value), "Nd" (port));
}

#endif

