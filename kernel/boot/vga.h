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

#include "stdint.h"

/**
 * Initiliaze the bootstrap vga screen starting at the specified position.
 *
 * @param x the start offset from the left border of the screen
 * @param y the start offset from the top brder of the screen
 */
void vga_start(uint8_t cursor_x, uint8_t cursor_y);

/**
 * Writes the string <str> on VGA screen following the current cursor
 * position. Moves the cursor forward.
 *
 * @param str the string to put on the screen
 * @param len the length of the <str> string
 */
void vga_putbytes(const char *str, int len);

#endif

