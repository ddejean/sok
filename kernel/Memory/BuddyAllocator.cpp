/*
 * Copyright (C) 2012, the Simple Object Kernel project.
 *
 * BuddyAllocator.cpp: buddy allocator implementation.
 * by Damien Dejean <djod4556@yahoo.fr>
 */

#include "stdint.h"
#include "stdio.h"
#include "assert.h"
#include "BuddyAllocator.h"

BuddyAllocator::BuddyAllocator(struct freeblock *freeAreas,
                               uint32_t capacities,
                               char *heap,
                               uint32_t heapSize):
        _freeAreas(freeAreas),
        _capacities(capacities),
        _heap(heap),
        _heapSize(heapSize)
{
        uint32_t i;

        /* Clear all chunk links */
        for(i = 0; i < _capacities - 1; i++) {
                freeAreas[i].next = (struct freeblock*) NULL;
        }

        /* Declare all heap memory as one BIG chunk */
        freeAreas[_capacities - 1].next = (struct freeblock*) _heap;
        freeAreas[_capacities - 1].next->next = (struct freeblock*) NULL;

}

uint32_t BuddyAllocator::heapSize(void)
{
    return _heapSize;
}

/**
 * Compute the upper power of two that contains an number.
 * @param n the number from which we compute the power
 */
static uint32_t powerFromSize(uint32_t n)
{
        uint32_t power;

        n--;
        for(power = 0; n != 0; power++, n >>= 1);

        return (power < 2) ? 2 : power;
}


void* BuddyAllocator::alloc(size_t size)
{
	uint32_t sizePower;
        uint32_t power;
	struct freeblock *freeArea;
	struct freeblock *buddyArea;

    if (size == 0) {
        return NULL;
    } else if (size < 4) {
        size = 4;
    }

    sizePower = powerFromSize(size);
    power = sizePower;

	/* Heap is too small */
	if (sizePower > _capacities) {
		return NULL;
	}

        /* Look for the first fitting area */
	while (_freeAreas[power-1].next == NULL){
		power++;
		if (power > _capacities) {
		        return NULL;
		}
	}

	/* Get the free chunk */
	freeArea = _freeAreas[power-1].next;
	_freeAreas[power-1].next = _freeAreas[power-1].next->next;

        /* Split the chunk in buddies if needed */
	while (power > sizePower) {
		buddyArea = freeArea + ((1 << (power-1))/sizeof(struct freeblock));
                assert(buddyArea != NULL);
		buddyArea->next = _freeAreas[power-2].next;
		_freeAreas[power-2].next = buddyArea;
		power--;
	}

	return freeArea;

}

void *BuddyAllocator::myBuddyAddress(void *me, size_t mySize)
{
        return (void*) ((((uint64_t)me - (uint64_t)_heap)^(uint64_t)mySize) + (uint64_t)_heap);
}

void BuddyAllocator::free(void *chunk, size_t size)
{
	uint32_t power ;
	struct freeblock *potentialBuddy;
	struct freeblock *matchingBuddy;

    if (chunk == NULL || size == 0) {
        return;
    }

    if (size < 4) {
        size = 4;
    }

    power = powerFromSize(size);
    size = (size_t) 1 << power;

	matchingBuddy = (struct freeblock *) myBuddyAddress(chunk, size);
    assert(matchingBuddy != NULL);

	potentialBuddy = &(_freeAreas[power-1]);

	while (potentialBuddy != NULL && potentialBuddy->next != NULL) {
		if (potentialBuddy->next == matchingBuddy) {
			potentialBuddy->next = potentialBuddy->next->next;
			/* Is it the left or the right buddy ? */
			chunk = (matchingBuddy < (struct freeblock*) chunk) ? (void*) matchingBuddy : chunk;

			/* Look for a bigger buddy */
            potentialBuddy = &(_freeAreas[power]);
			power++;

			/* New buddy address */
			size *= 2;
			matchingBuddy = (struct freeblock *) myBuddyAddress(chunk, size);
		} else {
			potentialBuddy = potentialBuddy->next;
		}
	}

	/* Finally chain the buddy */
	((struct freeblock*) chunk)->next = _freeAreas[power-1].next;
	_freeAreas[power-1].next = (struct freeblock*) chunk;
}

