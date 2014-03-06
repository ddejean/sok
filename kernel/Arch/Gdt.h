/*
 * Gdt.h
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Intel's x86 Global Descriptor table representation.
 */

#ifndef _GDT_H_
#define _GDT_H_

#include <assert.h>
#include <stdint.h>
#include "SegmentDescriptor.h"

/* @see Intel Software Developer's Manual, Volume 3A, 3.5.1 */
#define GDT_MAX_COUNT   8192

class Gdt {
private:
    uint32_t mCount;
    RawSegmentDescriptor *mRawGdt;

public:
    /**
     * Initialize a Global Descriptor Table representation.
     * Protected to ensure this class is extended.
     * @param rawGdt a reference on the raw GDT table.
     * @param count number of available GDT entries.
     *
     * @pre rawGdt != NULL
     *      rawGdt is aligned on 8 byte boundary
     *      1 < count <= GDT_MAX_COUNT
     */
    Gdt(RawSegmentDescriptor *rawGdt, uint32_t count);

    /**
     * GDT linear base address as expected by the CPU.
     * @return the linear address of the raw GDT, aligned on 8 byte boundary.
     * @see Intel Developer's Manual Volume 3a, section 3.5.1.
     */
    uint32_t getBaseAddress(void);

    /**
     * GDT limit.
     * @return the limit, ie the GDT size, a multiple of 8 bytes minus 1.
     * @see Intel Developer's Manual Volume 3a, section 3.5.1.
     */
    uint16_t getLimit(void);

    /**
     * Inserts a descriptor in teh GDT at the specified index.
     * @param index insertion index in the table.
     * @param desc the descriptor to insert.
     */
    void insert(uint32_t index, SegmentDescriptor *desc);
};

#endif /* _GDT_H_ */
