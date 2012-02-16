/*
 * vga.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * VGA support for first kernel stage.
 */

#ifndef _VGA_H_
#define _VGA_H_

/**
 * Writes the string <str> on VGA screen following the current cursor
 * position. Moves the cursor forward.
 *
 * @param str the string to put on the screen
 * @param len the length of the <str> string
 */
void vga_putbytes(const char *str, int len);

/**
 * Wipes the screen.
 */
void vga_clear(void);

#endif

