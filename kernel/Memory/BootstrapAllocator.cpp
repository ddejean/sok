/*
 * Simple Object Kernel
 *
 * BootstrapAllocator.c: bootstrap allocator implementation based on a buddy
 * system.
 *
 */

#include "BootstrapAllocator.h"
#include "string.h"

/* Allocator heap size: the size is computed like this: 2^BOOTSTRAP_POWER */
#ifndef         BOOTSTRAP_POWER
#define         BOOTSTRAP_POWER         20
#endif

/* Allocator heap size */
#define         BOOTSTRAP_HEAP_SIZE     (1 << BOOTSTRAP_POWER)

/* Allocator size must be a power of two, if not the following fails */
#if ((BOOTSTRAP_HEAP_SIZE & (BOOTSTRAP_HEAP_SIZE - 1)) != 0)
#error BOOTSTRAP_HEAP_SIZE must be a power of two !
#endif

/* Allocator heap */
char memoryHeap[BOOTSTRAP_HEAP_SIZE];

/* Free area table for the allocator*/
struct freeblock freeAreas[BOOTSTRAP_POWER];


/* False singleton implementation */
static uint8_t allocator[sizeof(BootstrapAllocator)];


BootstrapAllocator::BootstrapAllocator():BuddyAllocator(freeAreas,
                                                        BOOTSTRAP_POWER,
                                                        memoryHeap,
                                                        BOOTSTRAP_HEAP_SIZE){};

void* BootstrapAllocator::operator new(size_t size)
{
        (void)size;
        return (void*) &allocator;
}

void BootstrapAllocator::operator delete(void *) {};

BootstrapAllocator* BootstrapAllocator::mInstance = (BootstrapAllocator*) NULL;

BootstrapAllocator* BootstrapAllocator::getInstance(void)
{
        if (BootstrapAllocator::mInstance == NULL) {
                BootstrapAllocator::mInstance = new BootstrapAllocator();
        }
        return BootstrapAllocator::mInstance;
}

void BootstrapAllocator::reset(void)
{
       mInstance =  new BootstrapAllocator();
}

