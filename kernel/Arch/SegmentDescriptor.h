/*
 * SegmentDescriptor.h
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Describes a Global Descriptor Table entry.
 * See Intel System Programming Guide Volume 3A, section 5.2.
 */

#ifndef _SEGMENT_DESCRIPTOR_H_
#define _SEGMENT_DESCRIPTOR_H_

#include "stdint.h"

/* A segment descriptor is a a simple 64 bits int */
typedef uint64_t RawSegmentDescriptor;

/*
 * SegmentDescriptor object representation.
 * Allows to create a SegmentDescriptor easily and manipulate it without flags, offset
 * adn such complexity.
 */
class SegmentDescriptor {
private:
    uint32_t mBase;
    uint32_t mLimit;
    uint16_t mFlags;

    /* Only allow builders */
    SegmentDescriptor(void);

    /* Allow internal consistency checks */
    bool isSystemDescriptor(void);
    bool isCodeDescriptor(void);
    bool isDataDescriptor(void);

public:
    /* Common segment properties. */
    SegmentDescriptor* withBaseAddress(uint32_t baseAddress);
    SegmentDescriptor* withLimit(uint32_t limit);
    SegmentDescriptor* withKernelCredential(void);
    SegmentDescriptor* withUserCredential(void);
    SegmentDescriptor* withPageGranularity(void);
    SegmentDescriptor* markedAsPresent(void);
    SegmentDescriptor* for32bitProtectedMode(void);

    /* Code segment only */
    SegmentDescriptor* withReadPermission(void);

    /* Data segment only */
    SegmentDescriptor* withWritePermission(void);

    /* System segment only */
    enum SystemSegmentType {
        TSS_16BIT_AVAIL = 1,
        LDT             = 2,
        TSS_16BIT_BUSY  = 3,
        CALL_GATE_16BIT = 4,
        TASK_GATE       = 5,
        INT_GATE_16BIT  = 6,
        TRAP_GATE_16BIT = 7,
        TSS_32BIT_AVAIL = 9,
        TSS_32BIT_BUSY  = 11,
        CALL_GATE_32BIT = 12,
        INT_GATE_32BIT  = 14,
        TRAP_GATE_32BIT = 15,
    };
    SegmentDescriptor *withSystemType(enum SystemSegmentType type);

    /**
     * Returns a segment descriptor in cpu-readable format.
     */
    RawSegmentDescriptor toRawSegmentDescriptor(void);

    /* Builders */
    static SegmentDescriptor* aSystemSegmentDescriptor(void);
    static SegmentDescriptor* aCodeSegmentDescriptor(void);
    static SegmentDescriptor* aDataSegmentDescriptor(void);
    static SegmentDescriptor* aNullSegmentDescriptor(void);
};

#endif /* _SEGMENT_DESCRIPTOR_H__ */
