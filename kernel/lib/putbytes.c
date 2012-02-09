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

#include "stddef.h"
#include "putbytes.h"

/* Callback pointer used by print lib to send generated strings to output */
void (*putbytes)(const char *, int) = NULL;

void putbytes_callback(void (*cb)(const char *, int))
{
        putbytes = cb;
}

