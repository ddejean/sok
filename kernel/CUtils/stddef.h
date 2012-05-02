/*
 * stddef.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Standard C definitions.
 */

#ifndef _STDDEF_H_
#define _STDDEF_H_

/**
 * Definition of NULL pointer.
 */
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void*)0)
#endif

/**
 * Standard size type.
 */
typedef unsigned int size_t;

/**
 * Offset of a field in it's structure.
 */
#define offsetof(type,field)      ((unsigned long) &(((type*)0)->member))

#endif

