/*
 * qemu.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * QEMU debug console support.
 */

#ifndef _QEMU_H_
#define _QEMU_H_

/**
 * Writes the string <str> on QEMU debug console.
 *
 * @param str the string to put on the console
 * @param len the length of the <str> string
 */
void qemu_putbytes(const char *str, int len);

#endif

