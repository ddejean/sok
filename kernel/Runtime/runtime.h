/*
 * runtime.h
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Defines an API to setup and manage C++ kernel runtime.
 */

#ifndef _RUNTIME_H_
#define _RUNTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Memory/Allocator.h"

/*
 * ctor_t: constructor function types.
 */

typedef void (*ctor_t)(void);

/*
 * Static constructor location. Should be provided by linker script.
 * @see Boot/kernel.lds
 */
extern ctor_t _ctors_start[];
extern ctor_t _ctors_end[];

/**
 * Initialize the runtime environment calling C++ static objects constructors.
 * @param the bootstrap allocator to set up.
 */
extern void runtime_init(void);

/**
 * Injects an allocator to the runtime as the main allocator.
 * @param 
 */
extern void runtime_inject_allocator(Allocator *);

#ifdef __cplusplus
}
#endif

#endif /* _RUNTIME_H_ */
