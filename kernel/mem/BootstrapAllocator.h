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
                static BootstrapAllocator *_instance;
                BootstrapAllocator();
                void* operator new(size_t);

        public:
                /* Partial singleton implementation */
                static BootstrapAllocator *getInstance(void);
};

#endif /*_BOOTSTRAP_ALLOCATOR_H_ */

