/*
 * assert.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Assert wrapper.
 */

#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "stdio.h"

#define assert(cond)    do {                                                                                                            \
                                if (!(cond)) {                                                                                          \
                                        printf("%s (%s:%d): Assertion \"%s\" failed.", __FILE__, __func__, __LINE__, #cond);            \
                                }                                                                                                       \
                        } while (0)

#endif
