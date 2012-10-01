/*
 * gcc-pure-virtual.c
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Implements the fallback for unresolved calls to virtual methods.
 */

#include "panic.h"
#include "stddef.h"

/**
 * Called when a call to a virtual method failed because no pretendant were
 * found. Raises a fatal error.
 */
extern "C" void __cxa_pure_virtual(void)
{
        panic("%s: %s\n", __func__, "Virtual call resolution failed");
}

