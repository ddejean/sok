/*
 * Simple Object Kernel
 *
 * BootstrapAllocator.h: Bootstrap allocator for memory management specification.
 * Provides a simple memory allocator, on a pre-mapped memory area, based on the
 * budy algorithm.
 * Implemented as a singleton class, BUT, as we don't have any allocator yet, we
 * have to keep a public ctor.
 *
 */

#ifndef _BOOTSTRAP_ALLOCATOR_H_
#define _BOOTSTRAP_ALLOCATOR_H_

#include "stdint.h"
#include "stddef.h"
#include "BuddyAllocator.h"

class BootstrapAllocator: public BuddyAllocator {
        private:
                /* Singleton implementation */
                static BootstrapAllocator *mInstance;
                BootstrapAllocator();
                void* operator new(size_t);
                void  operator delete(void *);

        public:
                /*
                 * Singleton implementation: retrieve the instance of the
                 * allocator inside the singleton.
                 */
                static BootstrapAllocator *getInstance(void);

                /*
                 * Reset the allocator state. Beware, this will destroy memory
                 * allocation mapping and data in the allocated chunks.
                 * For testing purpose essentially.
                 */
                static void reset(void);
};

#endif /*_BOOTSTRAP_ALLOCATOR_H_ */

