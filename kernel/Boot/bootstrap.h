/*
 * bootstrap.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Defines tools used for the kernel bootstrap.
 */

#ifndef _BOOTSTRAP_H_
#define _BOOTSTRAP_H_

/**
 * Kernel offset of virtual address space.
 */
#define KERNEL_BASE     0xC0000000

/**
 * Tors limits;
 */
extern void (*_ctors_start)(void);
extern void (*_ctors_end)(void);
extern void (*_dtors_start)(void);
extern void (*_dtors_end)(void);

#endif

