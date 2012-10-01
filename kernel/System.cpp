/*
 * System.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * System manager implementation.
 */

#include "System.h"
#include "assert.h"
#include "Memory/BootstrapAllocator.h"


/* Singleton instance */
System* System::mInstance = NULL;


void* System::operator new(size_t size)
{
    BootstrapAllocator *ba = BootstrapAllocator::getInstance();
    return (void*) ba->alloc(size);
}


System* System::getInstance(void)
{
    if (System::mInstance == NULL) {
        System::mInstance = new System();
    }
    return System::mInstance;
}


bool System::init(struct boot_context *context)
{
    assert(context != NULL);
    assert(boot_context_check(context));

    /* Define an allocator for early initializations */
    mAllocator = BootstrapAllocator::getInstance();
    assert(mAllocator != NULL);

    /* From here, everybody can get the system allocator. */
    return true;
}


Allocator* System::getAllocator(void)
{
    assert(mAllocator != NULL);
    return mAllocator;
}

