/*
 * Copyright (C) 2012, the Simple Object Kernel project.
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Allocator.h: Interface for a memory allocator.
 */

#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <stdint.h>
#include <stddef.h>

class Allocator {
    private:
        /** A reference counter on this allocator */
        int mRefCounter;

    public:

        Allocator();
        ~Allocator();

        /**
         * Allocates a chunk memory of <size> bytes.
         *
         * @param size the size of the chunk to allocate.
         * @return a reference on the beggining of the chunk.
         */
        virtual void *alloc(size_t size) = 0;

        /**
         * Frees the provided chunk of memory.
         *
         * @param chunk a reference on the chunk to free.
         * @param size the size of the provided chunk.
         */
        virtual void free(void *chunk, size_t size) = 0;

        /**
         * Takes a reference on the allocator, the allocator will fail
         * on destruction if the reference counter is not null.
         */
        void takeRef();

        /**
         * Releases a reference on the allocator. The corresponding must
         * have been taken before.
         */
        void releaseRef();
};

#endif /* _ALLOCATOR_H_ */

