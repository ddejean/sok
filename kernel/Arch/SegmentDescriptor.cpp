/*
 * SegmentDescriptor.h
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Segment descriptor manipulation implementation.
 * See Intel System Programming Guide Volume 3A, section 5.2.
 */

#include "assert.h"
#include "SegmentDescriptor.h"

/* Set of macros to manipulate descriptor flags */
#define SET_SYSTEM_DESCRIPTOR(flags)   do { flags &= 0xFFEF; } while (0)
#define IS_SYSTEM_DESCRIPTOR(flags)    ((flags & 0x0010) == 0)

#define SET_CODE_DESCRIPTOR(flags)     do { flags |= 0x0018; } while(0)
#define IS_CODE_DESCRIPTOR(flags)      ((flags & 0x0018) == 0x0018)

#define SET_DATA_DESCRIPTOR(flags)     do { flags |= 0x0010; flags &= 0xFFF7; } while (0)
#define IS_DATA_DESCRIPTOR(flags)      ((flags & 0x0018) == 0x0010)

#define DPL_MASK                       0xFF9F
#define DPL_RING0                      0x0000
#define DPL_RING3                      0x0060

#define GRANULARITY_MASK               0x7FFF
#define GRANULARITY_PAGE               0x8000

#define PRESENT_MASK                   0xFF7F
#define PRESENT_BIT                    0x0080

#define PROTECTED_MODE_MASK            0xBFFF
#define PROTECTED_MODE_BIT             0x4000

#define CODE_READ_MASK                 0xFFFD
#define CODE_READ_BIT                  0x0002

#define DATA_WRITE_MASK                CODE_READ_MASK
#define DATA_WRITE_BIT                 CODE_READ_BIT

#define TYPE_MASK                      0xFFF0

SegmentDescriptor::SegmentDescriptor(void):
    mBase(0), mLimit(0), mFlags(0)
{
}

bool SegmentDescriptor::isSystemDescriptor(void)
{
    return IS_SYSTEM_DESCRIPTOR(this->mFlags);
}

bool SegmentDescriptor::isCodeDescriptor(void)
{
    return IS_CODE_DESCRIPTOR(this->mFlags);
}

bool SegmentDescriptor::isDataDescriptor(void)
{
    return IS_DATA_DESCRIPTOR(this->mFlags);
}

SegmentDescriptor* SegmentDescriptor::withBaseAddress(uint32_t baseAddress)
{
    this->mBase = baseAddress;
    return this;
}

SegmentDescriptor* SegmentDescriptor::withLimit(uint32_t limit)
{
    this->mLimit = limit & 0x000FFFFF;
    return this;
}

SegmentDescriptor* SegmentDescriptor::withKernelCredential(void)
{
    this->mFlags = (this->mFlags & DPL_MASK) | DPL_RING0;
    return this;
}

SegmentDescriptor* SegmentDescriptor::withUserCredential(void)
{
    this->mFlags = (this->mFlags & DPL_MASK) | DPL_RING3;
    return this;
}

SegmentDescriptor* SegmentDescriptor::withPageGranularity(void)
{
    this->mFlags = (this->mFlags & GRANULARITY_MASK) | GRANULARITY_PAGE;
    return this;
}

SegmentDescriptor* SegmentDescriptor::markedAsPresent(void)
{
    this->mFlags = (this->mFlags & PRESENT_MASK) | PRESENT_BIT;
    return this;
}

SegmentDescriptor* SegmentDescriptor::for32bitProtectedMode(void)
{
    this->mFlags = (this->mFlags & PROTECTED_MODE_MASK) | PROTECTED_MODE_BIT;
    return this;
}

SegmentDescriptor* SegmentDescriptor::withReadPermission(void)
{
    assert(this->isCodeDescriptor());
    this->mFlags = (this->mFlags & CODE_READ_MASK) | CODE_READ_BIT;
    return this;
}

SegmentDescriptor* SegmentDescriptor::withWritePermission(void)
{
    assert(this->isDataDescriptor());
    this->mFlags = (this->mFlags & DATA_WRITE_MASK) | DATA_WRITE_BIT;
    return this;
}

SegmentDescriptor* SegmentDescriptor::withSystemType(enum SystemSegmentType type)
{
    assert(this->isSystemDescriptor());
    this->mFlags = (this->mFlags & TYPE_MASK) | (uint16_t)type;
    return this;
}

RawSegmentDescriptor SegmentDescriptor::toRawSegmentDescriptor(void)
{
    uint64_t hi = 0;
    uint64_t lo = 0;

    hi = (mBase & 0xFF000000) |      /* Base [31:24] */
         ((mFlags & 0xF0FFu) << 8) | /* Flags */
         (mLimit & 0x000F0000) |     /* Limit [19:16] */
         (mBase & 0x00FF0000) >> 16; /* Base [23:16] */

    lo = ((mBase & 0x0000FFFF) << 16) |
         (mLimit & 0xFFFF);

    return (hi << 32) | lo;
}

SegmentDescriptor* SegmentDescriptor::aSystemSegmentDescriptor(void)
{
    SegmentDescriptor *desc = new SegmentDescriptor();
    SET_SYSTEM_DESCRIPTOR(desc->mFlags);
    return desc;
}

SegmentDescriptor* SegmentDescriptor::aCodeSegmentDescriptor(void)
{
    SegmentDescriptor *desc = new SegmentDescriptor();
    SET_CODE_DESCRIPTOR(desc->mFlags);
    return desc;
}

SegmentDescriptor* SegmentDescriptor::aDataSegmentDescriptor(void)
{
    SegmentDescriptor *desc = new SegmentDescriptor();
    SET_DATA_DESCRIPTOR(desc->mFlags);
    return desc;
}

SegmentDescriptor* SegmentDescriptor::aNullSegmentDescriptor(void)
{
    return new SegmentDescriptor();
}
