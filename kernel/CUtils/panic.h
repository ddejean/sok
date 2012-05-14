/*
 * panic.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Gaëtan Morin
 *
 * Kernel panic.
 */

#ifndef _PANIC_H_
#define _PANIC_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Panic ends the execution of the kernel with an error message and a stack
 * trace. This function never returns to its caller (it blocks indefinitely).
 *
 * @param fmt a printf-like format string
 * @param ... format string parameters
 */
void panic(const char *fmt, ...)
        __attribute__((format (printf, 1, 2)));



#ifdef __cplusplus
}
#endif

#endif

