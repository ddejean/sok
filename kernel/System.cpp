/*
 * System.h
 *
 * Copyright (C) 2012-2013 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * System manager implementation.
 */

#include "System.h"
#include "assert.h"
#include "Memory/BootstrapAllocator.h"
#include "Memory/FrameManager.h"

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

void System::injectBootContext(struct boot_context *context)
{
    assert(context != NULL);
    assert(boot_context_check(context));
    mBootContext = context;
}

bool System::bootstrapSystem(void)
{
    unsigned memorySize;

    /* Define an allocator for early initializations */
    mAllocator = BootstrapAllocator::getInstance();
    assert(mAllocator != NULL);

    memorySize = (unsigned)mBootContext->memory_end - (unsigned)mBootContext->memory_start;
    FrameManager *fm = new FrameManager(mBootContext->memory_start,
            1 << 12,
            memorySize >> 12);
    (void)fm;
    /* From here, everybody can get the system allocator. */
    return true;
}


Allocator* System::getAllocator(void)
{
    assert(mAllocator != NULL);
    return mAllocator;
}

