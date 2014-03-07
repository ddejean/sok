/*
 * SokGdt.cpp
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Kernel Global Descriptor Table.
 */

#include <assert.h>
#include <stddef.h>
#include "SokGdt.h"

/*
 * CPU suitable Global Descriptor Table.
 * The GDT that we'll provide to CPU must follow the following requirements:
 *  - be aligned on 8 bytes boundary
 *  - contain a first unused descriptor (a null descriptor)
 *  - have a maximum size of 8192 entries.
 */
#define GDT_ENTRIES     64
#define GDT_SIZE        (GDT_ENTRIES * sizeof(RawSegmentDescriptor))

#define SELECTOR_TO_INDEX(x)     (x / sizeof(RawSegmentDescriptor))
static RawSegmentDescriptor kernelGdt[GDT_ENTRIES];


SokGdt::SokGdt(void) : Gdt(kernelGdt, GDT_ENTRIES)
{
}

SokGdt* SokGdt::withKernelCodeDescriptor(SegmentDescriptor *desc)
{
    assert(desc != NULL);
    this->insert(SELECTOR_TO_INDEX(KERNEL_CS), desc);
    return this;
}

SokGdt* SokGdt::withKernelDataDescriptor(SegmentDescriptor *desc)
{
    assert(desc != NULL);
    this->insert(SELECTOR_TO_INDEX(KERNEL_DS), desc);
    return this;
}

SokGdt* SokGdt::withUserCodeDescriptor(SegmentDescriptor *desc)
{
    assert(desc != NULL);
    this->insert(SELECTOR_TO_INDEX(USER_CS), desc);
    return this;
}

SokGdt* SokGdt::withUserDataDescriptor(SegmentDescriptor *desc)
{
    assert(desc != NULL);
    this->insert(SELECTOR_TO_INDEX(USER_DS), desc);
    return this;
}

SokGdt* SokGdt::withTssDescriptor(SegmentDescriptor *desc)
{
    assert(desc != NULL);
    this->insert(SELECTOR_TO_INDEX(TSS_SELECTOR), desc);
    return this;
}

SokGdt* SokGdt::theKernelGdt(void)
{
    return new SokGdt();
}
