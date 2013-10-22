/*
 * vga.c
 *
 * Copyright (C) 2012-2013 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * VGA screen implementation.
 * The IBM-PC VGA screen is a 80*25 framebuffer where it is possible to print
 * char directly on the screen. This is done by writing the chars at a standard
 * memory adress (modulo the kernel offset).
 * Some graphic hardware registers provides a way to moves the cursor on the
 * screen.
 */

#include "bootstrap.h"
#include "vga.h"
#include "cpu.h"
#include "string.h"
#include "stdint.h"

/* Hardware location of the char framebuffer */
#define VGA_BASE        0xB8000

/* VGA constants */
#define VGA_WIDTH       80
#define VGA_HEIGHT      25
#define VGA_CHAR_SIZE   2
#define VGA_BUFFER_SIZE (VGA_WIDTH * VGA_HEIGHT * VGA_CHAR_SIZE)
#define VGA_CURSOR_CMD  0x3D4
#define VGA_CURSOR_DATA 0x3D5
#define VGA_CURSOR_LOW  0x0F
#define VGA_CURSOR_HIGH 0x0E


/* Screen parameters */
static char *screen = (char*)VGA_BASE;
static const char color = 0x0F;  /* White fg, black bg */
static uint8_t x;
static uint8_t y;

/** 
 * Set VGA cursor to position (x, y)
 * @param cursor_x the x position of the cursor
 * @param cursor_y the y position of the cursor
 */
static inline void vga_set_cursor(uint8_t cursor_x, uint8_t cursor_y)
{
        uint16_t cursor;

        cursor = cursor_x + cursor_y * VGA_WIDTH;
        outb( VGA_CURSOR_LOW,            VGA_CURSOR_CMD);
        outb( (uint8_t)cursor,           VGA_CURSOR_DATA);
        outb( VGA_CURSOR_HIGH,           VGA_CURSOR_CMD);
        outb( (uint8_t)(cursor >> 8),    VGA_CURSOR_DATA);
}

/**
 * Scroll the display of one line to the top.
 */
static void vga_scroll(void)
{
	int i;
        char *pos = screen;
	size_t size = (VGA_HEIGHT - 1) * VGA_WIDTH * VGA_CHAR_SIZE;

	memmove((char*)VGA_BASE, (char*)(VGA_BASE + (VGA_WIDTH * VGA_CHAR_SIZE)), size);
	y = VGA_HEIGHT - 1;
	x = 0;
	for (i = 0; i < VGA_WIDTH; i++) {
		*(pos++) = ' ';
		*(pos++) = color;
	}
	vga_set_cursor(x, y);
	screen = (char*)(VGA_BASE + VGA_BUFFER_SIZE - (VGA_WIDTH * VGA_CHAR_SIZE));
}

/**
 * Forward the screen pointer and the visible cursor from one position.
 */
static void vga_step_forward(void)
{
	screen += VGA_CHAR_SIZE;
	if (++x == VGA_WIDTH) {
		x = 0;
		if (++y == VGA_HEIGHT)
			vga_scroll();
	}
}

/**
 * Rewind from one character.
 */
static void vga_step_back(void)
{
	screen -= VGA_CHAR_SIZE;
	if (x == 0) {
		x = VGA_WIDTH - 1;
		--y;
	} else {
		--x;
	}
}

/**
 * Process a char and print the corresponding symbol on the screen.
 * @param c the char to display
 */
static inline void vga_putchar(char c)
{
	int offset, i;

	if (c >= 32 && c <= 126) {
		*(screen)     = c;
		*(screen + 1) = color;
		vga_step_forward();
        } else if (c == '\b' && x != 0) {
                vga_step_back();
        } else if (c == '\t') {
		offset = 8 - x % 8;
		for (i = 0; i < offset; i++)
			vga_step_forward();
        } else if (c == '\n') {
		offset = VGA_WIDTH - x % VGA_WIDTH;
		for (i = 0; i < offset; i++)
			vga_step_forward();
        } else if (c == '\r') {
		while (x != 0)
			vga_step_back();
	}
}

/**
 * Blank the screen with whitespaces and put the cursor
 * at the beginning of the screen.
 */
static void vga_clear(void)
{
        int i;

        /* Reset screen parameters */
        x = 0;
        y = 0;
        /* Clear is */
        for (i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
                vga_putchar(' ');
        } 
        screen = (char*)VGA_BASE;
        x = 0;
        y = 0;
        /* Reset the cursor */
        vga_set_cursor(x, y);
}

/*
 * Public interaface implementation.
 * @see vga.h
 */

void vga_start(uint8_t cursor_x, uint8_t cursor_y)
{
        if (x > VGA_WIDTH || y > VGA_HEIGHT || (x == 0 && y == 0)) {
                vga_clear();
        } else {
                x = cursor_x;
                y = cursor_y;
        }
          
}

void vga_putbytes(const char *str, int len)
{
        int i;
        for (i = 0; i < len; i++) {
                vga_putchar(*str);
                str++;
        }
        vga_set_cursor(x, y);
}

