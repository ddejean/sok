/*
 * Simple Object Kernel
 *
 * boot-context.h: defines a structure that contains basic information obtained
 *      during boot until stage2.
 */

#ifndef _BOOT_CONTEXT_H_
#define _BOOT_CONTEXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define STAGE1_MAGIC    0xDEADC0DEu

/**
 * Collects information deduced during bootstrap sequence. Some helpers for
 * later initialisations.
 */
struct boot_context {
    unsigned int magic;     // Must be STAGE1_MAGIC and must always exist
    void *memory_start;     // Beginning and end of usable hardware memory
    void *memory_end;
    void *bootstrap_gdt;    // The GDT installed during bootstrap for early
                            // memory translation. Virtual address.
    int gdt_length;         // Length of the boostrap GDT.
};

/**
 * Checks that the provided struct is a boot_context structure.
 *
 * @param context a reference on the boot context structure.
 * @return 1 if the structure is valid, 0 otherwise.
 */
int boot_context_check(struct boot_context *context);

#ifdef __cplusplus
}
#endif

#endif /* _BOOT_CONTEXT_H_ */

