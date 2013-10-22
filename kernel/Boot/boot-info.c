/*
 * Simple Object Kernel
 *
 * boot-info.c: provides a structure that contains information gathered
 *              before and during the stage1 bootstrap process.
 */

#include "boot-info.h"
#include "bootstrap.h"
#include "multiboot.h"

/** The structure to provide boot information */
static struct boot_context info;

/** Kernel link-dependant symbols */
extern char bootstrap_gdt[];
extern char bootstrap_gdt_end[];
extern char _kernel_end[];

struct boot_context *boot_info_fill(void) {

        info.magic = STAGE1_MAGIC;
        info.bootstrap_gdt = (void*)bootstrap_gdt;
        info.gdt_length = (int)(bootstrap_gdt_end - bootstrap_gdt);
        info.memory_start = (void*)_kernel_end;
        info.memory_end = (void*) multiboot_mem_upper_address();

        return &info;
}

