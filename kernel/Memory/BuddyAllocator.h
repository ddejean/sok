/*
 * Copyright (C) 2012, the Simple Object Kernel project.
 *
 * BuddyAllocator.h: Small memory allocator based on buddy system algorithm.
 * by Damien Dejean <djod4556@yahoo.fr>
 */

#ifndef _BUDDY_ALLOCATOR_H_
#define _BUDDY_ALLOCATOR_H_

#include <stdint.h>
#include <stddef.h>

/* Free block: self contained link to the next one ! */
struct freeblock {
        struct freeblock *next;
};

class BuddyAllocator {
        private:
                /* Free area management */
                struct freeblock *_freeAreas;
                uint32_t _capacities;

                /*  Memory heap */
                char *_heap;
                uint32_t _heapSize;

                /* Find the address of my buddy chunk */
                void *myBuddyAddress(void *me, size_t mySize);

        public:
                BuddyAllocator(struct freeblock *freeAreas,    /* Free area table */
                               uint32_t capacities,             /* Number of free area sizes */
                               char *heap,
                               uint32_t heapSize);

                /* Allocator implementation */
                void *alloc(size_t size);
                void free(void *chunk, size_t size);
};

#endif /*_BUDDY_ALLOCATOR_H_ */

