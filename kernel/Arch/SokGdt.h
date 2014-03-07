/*
 * SokGdt.h
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Sok kernel Global Descriptor Table.
 */

#ifndef _SOKGDT_H_
#define _SOKGDT_H_

#include <stdint.h>
#include "Gdt.h"

/*
 * Segment selectors for segment registers as defined in this GDT.
 */
#define KERNEL_CS       0x08
#define KERNEL_DS       0x10
#define USER_CS         0x18
#define USER_DS         0x20
#define TSS_SELECTOR    0x28

class SokGdt: public Gdt {
private:
    /* Creation by builder only */
    SokGdt(void);

public:
    /*** Segment Descriptor setters ***/
    SokGdt *withKernelCodeDescriptor(SegmentDescriptor *);
    SokGdt *withKernelDataDescriptor(SegmentDescriptor *);
    SokGdt *withUserCodeDescriptor(SegmentDescriptor *);
    SokGdt *withUserDataDescriptor(SegmentDescriptor *);
    SokGdt *withTssDescriptor(SegmentDescriptor *);

    /**
     * Returns Sok kernel Global Descriptor Table.
     */
    static SokGdt* theKernelGdt(void);
};

#endif /* _SOKGDT_H_ */

