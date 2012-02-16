/*
 * Simple Object Kernel
 *
 * stage1.c: C part of the bootstrap. Do all architecture dependent
 *            and non abstractable initializations. Create a suitable
 *            environment for C++ execution.
 */

#include "vga.h"
#include "putbytes.h"
#include "stdio.h"

void stage1_main(unsigned int multiboot_magic, void *multiboot_info)
{
        (void) multiboot_magic;
        (void) multiboot_info;

        /* Prepare the display for this stage1 */
        putbytes_callback(vga_putbytes);
        vga_clear();

        /* Display a stage1 message */
        printf("%s\n", "Welcome on Simple Object Kernel !");

        while(1);
}

