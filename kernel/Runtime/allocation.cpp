/*
 * allocation.cpp
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Defines default allocation operators for classes that does not override them.
 * Manage
 */

#include "stdint.h"
#include "assert.h"
#include "Kernel/System.h"
#include "Memory/Allocator.h"

/**
 * Internal structure to manage a link between an object and its allocator, and
 * the object size.
 */
struct allocation_link {
    Allocator *myAllocator; // A reference on the proprietary allocator
    size_t mySize;          // Size of the object
    uint32_t magic;         // A magic to control memory corruption
};

/** Control magic */
#define ALLOCATION_MAGIC    0xBAADF00Du

/**
 * Allocates a chunk of memory for the object plus a small space for the
 * allocator link structure.
 *
 * @param size the size of the object we want to allocate. Must be positive.
 * @return a reference on the newly allocated object.
 */
static void *allocation_new(size_t size)
{
    System *system;
    Allocator *allocator;
    struct allocation_link *link;
    char *p;

    if (size == 0) {
        return NULL;
    }

    /* Get the memory chunk */
    system = System::getInstance();
    allocator = system->getAllocator();
    link = (struct allocation_link*) allocator->alloc(size + sizeof(struct allocation_link));

    if (link != NULL) {
        /* Prepare it for delivery */
        link->myAllocator = allocator;
        link->mySize = size;
        link->magic = ALLOCATION_MAGIC;

        /* Take a ref on the allocator */
        allocator->takeRef();

        /* Deliver the object */
        p = (char*)link;
        p += sizeof(struct allocation_link);
        return p;
    }

    return NULL;

}

void *operator new(size_t size)
{
    return allocation_new(size);
}
 
void *operator new[](size_t size)
{
    return allocation_new(size);
}


/**
 * Free an object using the right allocator.
 *
 * @param p reference on the object to free. Must not be NULL.
 */
static void allocation_delete(void *p)
{
    char *chunk;
    size_t size;
    Allocator *allocator;
    struct allocation_link *link;

    chunk = (char*) p;
    chunk -= sizeof(struct allocation_link);
    link = (struct allocation_link*) chunk;

    assert(link->magic == ALLOCATION_MAGIC);
    assert(link->myAllocator != NULL);
    assert(link->mySize > 0);
    allocator = link->myAllocator;
    size = link->mySize;

    allocator->releaseRef();
    allocator->free(chunk, size);
}

void operator delete(void *p)
{
    assert(p != NULL);
    allocation_delete(p);
}
 
void operator delete[](void *p)
{
    assert(p != NULL);
    allocation_delete(p);
}

