/*
 * backtrace.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Gaëtan Morin
 *
 * Backtrace Headers.
 */

#ifndef _BACKTRACE_H_
#define _BACKTRACE_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Backtrace unwinds the stack to find the addresses of the callers of the
 * enclosing function (the "stack trace"). Those addresses are written, in
 * order (innermost to outermost), into the given array.
 *
 * @param array a pointer array capable of holding at least {@code size}
 *        elements
 * @param size the maximum number of stack frames to unwind
 * @return the number of entries written into the array (between 0 and
 *        {@code size}, included).
 */
int backtrace(void **array, int size);


#ifdef __cplusplus
}
#endif

#endif
