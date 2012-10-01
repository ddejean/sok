/*
 * Copyright (C) 2012, the Simple Object Kernel project.
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Allocator.cpp: Base implementation for kernel allocators. Just implement a
 *                reference counter to ensure that the allocator is not
 *                destroyed before all objects have been released.
 */

#include "assert.h"
#include "Allocator.h"

Allocator::Allocator()
{
    /* New allocator, nobody reference it. */
    mRefCounter = 0;
}

Allocator::~Allocator()
{
    /* We cannot destroy the allocator if any object still reference it !*/
    assert(mRefCounter == 0);
}

/**
 * Takes a reference on the allocator, the allocator will fail
 * on destruction if the reference counter is not null.
 */
void Allocator::takeRef()
{
    assert(mRefCounter >= 0);
    mRefCounter++;
}

/**
 * Releases a reference on the allocator. The corresponding must
 * have been taken before.
 */
void Allocator::releaseRef()
{
    assert(mRefCounter > 0);
    mRefCounter--;
}

