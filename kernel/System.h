/*
 * System.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Basic System manager. This class acts as a system server, providing a way
 * to drive kernel basic but mandatory initialization steps. For example:
 *  - CPU minimal initialization
 *  - Provide a different allocator following the state of the boot process
 *  - Switch allocators when needed
 */

#include "Arch/boot-context.h"
#include "Memory/Allocator.h"

class System {
    private:
        /** Singleton instance. */
        static System *mInstance;
        
        /** The System instance is allocated into BootstrapAllocator. */
        void* operator new(size_t);

        /** Instance of the current allocator used by the whole system. */
        Allocator *mAllocator;

    public:
        /**
         * Provides the unique instance of the system server.
         *
         * @return a reference to the system instance. Must never be NULL
         * or there's a BIG bug.
         */
        static System *getInstance(void);

        /**
         * Basic system initialization:
         *  - Prepare CPU minimal tables
         *  - Choose an allocator for the current session.
         * Assert if something goes wrong.
         *
         * @param context the arch dependant context provided by previous
         *           stage. Never NULL, there's always some information to
         *           get from the previous boot sequences.
         *
         * @pre setContext() must have been called before.
         */
        bool init(struct boot_context *context);

        /**
         * Provides the allocator for the current system state. This allocator
         * may change may change during boot untilit reaches the kernel full
         * featured allocator.
         *
         * @return the instance of the allocator for the current boot stage.
         */
        Allocator* getAllocator(void);
};

