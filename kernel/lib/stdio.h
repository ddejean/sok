/*
 * stdio.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Standard output functions
 */

#ifndef __STDIO_H__
#define __STDIO_H__

#include "stdarg.h"

int printf(const char *__format, ...) __attribute__((format (printf, 1, 2)));
int vprintf(const char *__format, va_list __vl) __attribute__((format (printf, 1, 0)));
int sprintf(char *__dest, const char *__format, ...) __attribute__((format (printf, 2, 3)));
int snprintf(char *__dest, unsigned int __size, const char *__format, ...) __attribute__((format (printf, 3, 4)));
int vsprintf(char *__dest, const char *__format, va_list __vl) __attribute__((format (printf, 2, 0)));
int vsnprintf(char *__dest, unsigned int __size, const char *__format, va_list __vl) __attribute__((format (printf, 3, 0)));

#endif

