/*
 * multiboot.c
 *
 * Copyright (C) 2012-2013 - Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Multiboot utils implementation.
 * @see http://www.gnu.org/software/grub/manual/multiboot/multiboot.html
 */

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "bootstrap.h"
#include "multiboot.h"
#include "bootstrap.h"

/*
 * Backup multiboot structures.
 */
static multiboot_info_t mb_info;

static char bootloader_name[256];
static char cmdline_args[1024];

/*
 * Multiboot interface implementation.
 */
int multiboot_check(uint32_t magic)
{
        return (magic == MULTIBOOT_BOOTLOADER_MAGIC);
}

void multiboot_save(multiboot_info_t *mb)
{
        /* Save the main structure */
        memcpy(&mb_info, mb, sizeof(multiboot_info_t));

        /* Bootloader name */
        if ((mb_info.flags & MULTIBOOT_INFO_BOOT_LOADER_NAME)
            == MULTIBOOT_INFO_BOOT_LOADER_NAME) {
                strncpy(bootloader_name, (const char *)mb_info.boot_loader_name, 256);
        } else {
                bootloader_name[0] = '\0';
        }

        /* Command line arguments */
        if ((mb_info.flags & MULTIBOOT_INFO_CMDLINE) == MULTIBOOT_INFO_CMDLINE) {
                strncpy(cmdline_args, (const char *)mb_info.cmdline, 1024);
        } else {
                cmdline_args[0] = '\0';
        }
}

const char *multiboot_bootloader_name(void)
{
        if (bootloader_name[0] == '\0') {
                return NULL;
        } else {
                return bootloader_name;
        }
}

const char *multiboot_cmdline_args(void)
{
        if (cmdline_args[0] == '\0') {
                return NULL;
        } else {
                return cmdline_args;
        }
}

uint32_t multiboot_mem_upper_address(void)
{
        if ((mb_info.flags & MULTIBOOT_INFO_MEMORY) == MULTIBOOT_INFO_MEMORY) {
                uint32_t upper_address;
                /* Multiboot gives us the upper memory hole, in KB,
                 * minus 1 MB. */
                upper_address = mb_info.mem_upper + 1024u;
                /* Return a byte based address */
                return upper_address * 1024;
        } else {
                return 0xFFFFFFFFu;
        }
}

