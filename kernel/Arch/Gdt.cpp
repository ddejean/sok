/*
 * Gdt.cpp
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * GDT representation implementation.
 * It aims to ease GDT manipulation avioding common errors with CPU
 * configuration.
 */

#include <string.h>
#include "Gdt.h"

#define GDT_ALIGN_MASK     0x7

Gdt::Gdt(RawSegmentDescriptor *rawGdt, uint32_t count)
{
    assert(rawGdt != NULL);
    assert(count > 1); /* At least one NULL entry */
    assert(count <= GDT_MAX_COUNT);
    assert(((uint32_t)rawGdt & 0x7) == 0u);

    mRawGdt = rawGdt;
    mCount = count;
}

uint32_t Gdt::getBaseAddress(void)
{
    return (uint32_t)mRawGdt;
}

uint16_t Gdt::getLimit(void)
{
    /*
     * Limit definition as given by Intel Developer's Manual, Volume 3a, section
     * 3.5.1.
     */
    return mCount * sizeof(*mRawGdt) - 1;
}

void Gdt::insert(uint32_t index, SegmentDescriptor *desc)
{
    assert(index < GDT_MAX_COUNT);
    assert(desc != NULL);
    assert(mRawGdt != NULL);

    mRawGdt[index] = desc->toRawSegmentDescriptor();
}
