/*
 * bootstrap.h
 *
 * Copyright (C) 2012-2013 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Defines tools used for the kernel bootstrap.
 */

#ifndef _BOOTSTRAP_H_
#define _BOOTSTRAP_H_

/**
 * Tors limits;
 */
extern void (*_ctors_start)(void);
extern void (*_ctors_end)(void);
extern void (*_dtors_start)(void);
extern void (*_dtors_end)(void);


/**
 * First stack size: 16 KB.
 */
#define BOOTSTRAP_STACK_SIZE       (16*1024)
extern unsigned char boostrap_stack[];

#endif

