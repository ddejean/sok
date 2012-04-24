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
#include "mem/BootstrapAllocator.h"

void kernel_main(int argc, char **argv)
{
        (void)argc;
        (void)argv;

        printf("%s", "Running stage 2 ...\n");

        BootstrapAllocator *ba = BootstrapAllocator::getInstance();
        (void)ba;

}


#ifdef __cplusplus
}
#endif

