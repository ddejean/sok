/*
 * realmode.h 
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Real mode code must run between 0 and 1Mo. That's why real mode code is
 * linked appart the kernel binary and packed as data. At initialization,
 * we need to copy this code into low memory, at adress 0x2000.
 */

#ifndef _REALMODE_H_
#define _REALMODE_H_

/**
 * Copy real mode code to low memory.
 */
void realmode_setup(void);

#endif /* ! REALMODE_HEADER */

