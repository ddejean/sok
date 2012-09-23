/*
 * kernel.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * C++ kernel entry point declaration.
 */

#ifndef _KERNEL_H_
#define _KERNEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Arch/boot-context.h"

void kernel_main(struct boot_context *context, int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_H_ */

