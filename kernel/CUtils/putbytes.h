/*
 * putbytes.h
 *
 * Copyright (C) 2012 Simple Object Kernel project
 * by Damien Dejean <djod4556@yahoo.fr>
 *
 * Output wrapper for the print library. Print library creates printable
 * strings from format string, arguments and uses this callback to send
 * created string to destination.
 */

#ifndef _PUTBYTES_H_
#define _PUTBYTES_H_

/**
 * Affect the current putbytes callback with the callback provided in parameter
 */
void putbytes_callback(void (*)(const char *, int));

#endif
