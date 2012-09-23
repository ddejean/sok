/*
 * Simple Object Kernel
 *
 * boot-info.h: provides a way to retrieve the boot_context structure filled
 *              with gathered information.
 */

#ifndef _BOOT_INFO_H_
#define _BOOT_INFO_H_

#include "Arch/boot-context.h"

/**
 * Fills the boot_context structure with accurates data extracted from the
 * bootstrap process.
 *
 * @return a reference on a information structure. Is never NULL or it is a
 *         bug.
 */
struct boot_context *boot_info_fill(void);

#endif /* _BOOT_INFO_H_ */

