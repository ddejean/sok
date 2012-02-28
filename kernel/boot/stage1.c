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
#include "string.h"
#include "multiboot.h"

/**
 * Abstract displayt initialization, depending on compilation parameters.
 */
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

/**
 * Transform multiboot command line and standard C arguments.
 *
 * @param mb_args the oneline multiboot arguments
 * @param argc a pointeur on the argument count variable. We will be filled
 *        with the amount of arguments.
 *
 * @return a pointer on the tab of arguments.
 */
char **stage1_argumentize(const char *mb_args, int *argc)
{
        static char *argv[32];
        static char arguments[1024];

        char *c;
        int count;

        /* We have no argument to parse */
        if (mb_args == NULL || mb_args[0] == '\0') {
                argv[0] = NULL;
                *argc = 0;
        }

        /* Save the original argument list */
        strncpy(arguments, mb_args, 1024);

        /* Create the argument table */
        for (c = arguments, count = 1, argv[0] = arguments;
             *c != '\0' && count < 32;
             c++) {
                switch (*c) {
                        case ' ':
                        case '\t':
                                *c = '\0';
                                count++;
                                argv[count] = (c + 1);
                                break;
                        default:
                                /* Ignore the char ... */
                                break;
                }
        }
 
        *argc = count;
        return argv;
}

/**
 * Entry point of kernel first stage.
 */
void stage1_main(uint32_t multiboot_magic, multiboot_info_t *multiboot_info)
{
        const char *bootloader_name;
        const char *cmdline_args;
        int i;
        int argc;
        char **argv;

        /* Prepare a simple debug display */
        stage1_setup_display();

        /* Check we have been loaded by a compliant mutliboot loader */
        if (multiboot_check(multiboot_magic)) {
                multiboot_save(multiboot_info);
        } else {
                printf("%s\n", "Boot failure: Simple Object Kernel only support multiboot compliant loaders.");
                return;
        }

        /* Introduction messages */
        printf("%s\n", "Simple Object Kernel is booting ...");

        bootloader_name = multiboot_bootloader_name();
        if (bootloader_name != NULL) {
                printf("Loaded by %s\n", bootloader_name);
        }

        /* Parse command line arguments for stage 2 (main C++ kernel) */
        cmdline_args = multiboot_cmdline_args();
        argv = stage1_argumentize(cmdline_args, &argc);

        if (cmdline_args != NULL) {
                printf("Kernel arguments: ");
                for (i = 0; i < argc; i++) {
                        printf("%s ", argv[i]);
                }
                printf("\n");
        }

        /* Call constructors list */

        /* Call C++ kernel */

        /* Call destructors */

        while(1);
}

