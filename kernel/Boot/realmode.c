/*
 * realmode.h 
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Real mode setup implementation.
 */

#include "stddef.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "bootstrap.h"

/**
 * Code beacons: beginning and end of the real mode code.
 */
extern char _real_mode_start[];
extern char _real_mode_end[];

void realmode_setup(void)
{
        char *code_location;
        size_t code_size;

        code_location = (char*)(KERNEL_BASE + 0x2000);
        code_size = (size_t)(_real_mode_end - _real_mode_start);

        memcpy(code_location,  (char*)_real_mode_start, code_size);
}

