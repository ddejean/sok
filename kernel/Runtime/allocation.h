/*
 * allocation.h
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Defines a private API for runtime functions.
 */

#ifndef _ALLOCATION_H_
#define _ALLOCATION_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Compile error if we're not in the runtime itself */
#ifndef RUNTIME
#    error "This header should not be included outside the runtime."
#endif

#include "Memory/Allocator.h"

/**
 * Provides the current runtime allocator.
 * @return the current runtime allocator.
 *
 * @note the allocator should not be cached and always retrieved through this
 * method unless you know precisely what you are doing.
 */
Allocator *runtime_get_allocator(void);

#ifdef __cplusplus
}
#endif

#endif /* _ALLOCATION_H_ */
