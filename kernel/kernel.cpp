/*
 * kernel.cpp
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * C++ kernel entry point.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "assert.h"
#include "kernel.h"
#include "System.h"


void kernel_main(struct boot_context *context, int argc, char **argv)
{
        System *system = NULL;
        (void)argc;
        (void)argv;

        printf("%s\n", "Running stage 2 ...");

        system = System::getInstance();
        assert(system != NULL);

        /* Ensure the system has a minimal initialization:
         *  - CPU is ready to be manipulated
         *  - We have a first step allocator
         */
        system->init(context);

        /*
         * From this point we're uder the aegis of the BootstrapAllocator, be
         * cautious with memory.
         */
        assert(system->getAllocator() != NULL);

        /* Now we're using the real, dynamic, full featured allocator */
        //TODO
}


#ifdef __cplusplus
}
#endif

