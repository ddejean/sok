/*
 * runtime.cpp
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Runtime API interface implementation.
 */

#include "assert.h"
#include "runtime.h"
#include "Memory/Allocator.h"

/**
 * Runtime current allocator that will be used by new/delete operators.
 */
static Allocator *current_allocator;


void runtime_init(void)
{
    unsigned long ctors_count;

    ctors_count = ((unsigned long)_ctors_end - (unsigned long)_ctors_start) / sizeof(ctor_t);

    for (unsigned i = 0; i < ctors_count; i++) {
        _ctors_start[i]();
    }
}

void runtime_inject_allocator(Allocator *a)
{
    assert(a != NULL);
    current_allocator = a;
}

extern "C" Allocator *runtime_get_allocator(void)
{
    assert(current_allocator != NULL);
    return current_allocator;
}
