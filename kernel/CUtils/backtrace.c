/*
 * backtrace.c
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Gaëtan Morin
 *
 * Stub (weak) backtrace implementation.
 * Will be overriden by the implementation provided by Arch module.
 */

#include "backtrace.h"

int weak_backtrace(void **array, int size) {
        (void)array;
        (void)size;
        return 0;
}

int backtrace(void **, int) __attribute__((weak, alias("weak_backtrace")));
