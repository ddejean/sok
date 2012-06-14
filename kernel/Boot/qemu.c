/*
 * qemu.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * QEMU debug console support. Every char written on the QEMU port
 * is printed on the qemu debug console. Use -debugcon flag to enable
 * it on QEMU run.
 */

#ifndef _QEMU_H_
#define _QEMU_H_

#include "cpu.h"

#define QEMU_PORT       0xE9

void qemu_putbytes(const char *str, int len)
{
        int i;

        for (i = 0; i < len && *str != '\0'; i++, str++) {
           outb(*str, QEMU_PORT);
        }
}

#endif

