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
#include "kernel.h"
#include "Memory/BootstrapAllocator.h"


void kernel_main(struct boot_context *context, int argc, char **argv)
{
        (void)context;
        (void)argc;
        (void)argv;

        printf("%s\n", "Running stage 2 ...");
        BootstrapAllocator *ba = BootstrapAllocator::getInstance();
        (void)ba;

}


#ifdef __cplusplus
}
#endif

