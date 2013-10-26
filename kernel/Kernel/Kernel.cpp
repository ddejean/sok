/*
 * kernel.cpp
 *
 * Copyright (C) 2012-2013 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * C++ kernel entry point.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "assert.h"
#include "Kernel.h"
#include "System.h"


void kernel_main(struct boot_context *context, int argc, char **argv)
{
        System *system = NULL;
        (void)argc;
        (void)argv;

        printf("%s\n", "Running stage 2 ...");

        system = System::getInstance();
        assert(system != NULL);
        system->injectBootContext(context);

        /* Bootstrap:  */
        system->bootstrapSystem();
}


#ifdef __cplusplus
}
#endif

