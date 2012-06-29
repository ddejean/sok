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
                struct freeblock *mFreeAreas;
                uint32_t mCapacities;

                /*  Memory heap */
                char *mHeap;
                uint32_t mHeapSize;

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

                /* Convenience */
                uint32_t heapSize(void);
};

#endif /*_BUDDY_ALLOCATOR_H_ */

