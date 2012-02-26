/*
 * Simple Object Kernel
 *
 * stage1.c: C part of the bootstrap. Do all architecture dependent
 *            and non abstractable initializations. Create a suitable
 *            environment for C++ execution.
 */

#include "vga.h"
#include "qemu.h"
#include "putbytes.h"
#include "stdio.h"
#include "stddef.h"

static void stage1_setup_display(void)
{
#ifdef QEMU_DEBUG
        putbytes_callback(qemu_putbytes);
#elif  VGA_DEBUG
        vga_start(0, 0);
        putbytes_callback(vga_putbytes);
#else
        putbytes_callback(NULL);
#endif
}

void stage1_main(uint32_t multiboot_magic, void *multiboot_info)
{
        (void) multiboot_magic;
        (void) multiboot_info;

        /* Prepare a simple debug display */
        stage1_setup_display();

        /* Display a stage1 message */
        printf("%s\n", "Welcome on Simple Object Kernel !");

        while(1);
}

