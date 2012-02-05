/*
 * Simple Object Kernel
 *
 * stage1.c: C part of the bootstrap. Do all architecture dependent
 *            and non abstractable initializations. Create a suitable
 *            environment for C++ execution.
 */

void stage1_main(unsigned int multiboot_magic, void *multiboot_info)
{
        char *fb = (char*)0xC00B8000;
        char *msg = "Welcome on Simple Object Kernel project !";

        (void) multiboot_magic;
        (void) multiboot_info;

        while (*msg != '\0') {
                *fb = *msg;
                msg++;
                fb += 2;
        }

        while(1);
}

