/*
 * Simple Object Kernel
 *
 * boot-context.c: utilities for boot context manipulation.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "boot-context.h"
#include "assert.h"
#include "stddef.h"

/* Checks that the provided struct is a boot_context structure. */
int boot_context_check(struct boot_context *context)
{
        assert(context != NULL);
        return (context->magic == STAGE1_MAGIC);
}

