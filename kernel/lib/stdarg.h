/*
 * stdarg.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.>
 *
 * Argument list features.
 */

#ifndef __STDARG_H__
#define __STDARG_H__

typedef __builtin_va_list va_list;
#define va_start(v,l)   __builtin_va_start((v),l)
#define va_end          __builtin_va_end
#define va_arg          __builtin_va_arg

#endif
