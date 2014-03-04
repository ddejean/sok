#include "TestSegmentDescriptor.h"
#include "Arch/SegmentDescriptor.h"
#include <stdio.h>

/* Kernel flat segments (no offset, limit = 4G) */
#define KERNEL_FLAT_CODE_SEGMENT   0x00CF9A000000FFFFu
#define KERNEL_FLAT_DATA_SEGMENT   0x00CF92000000FFFFu
/* User flat segments  */
#define USER_FLAT_CODE_SEGMENT   0x00CFFA000000FFFFu
#define USER_FLAT_DATA_SEGMENT   0x00CFF2000000FFFFu

void TestSegmentDescriptor::testNullDescriptor(void)
{
    SegmentDescriptor *desc = SegmentDescriptor::aNullSegmentDescriptor();
    TS_ASSERT(desc != 0);

    TS_ASSERT_EQUALS((uint64_t)desc->toRawSegmentDescriptor(), (uint64_t)0);
}

void TestSegmentDescriptor::testProtectedModeKernelFlatCodeDescriptor(void)
{
    SegmentDescriptor *desc;

    desc = SegmentDescriptor::aCodeSegmentDescriptor()
       ->withBaseAddress(0u)
       ->withLimit(0xFFFFF)
       ->withKernelCredential()
       ->withPageGranularity()
       ->markedAsPresent()
       ->for32bitProtectedMode()
       ->withReadPermission();
    TS_ASSERT_EQUALS((uint64_t)desc->toRawSegmentDescriptor(), KERNEL_FLAT_CODE_SEGMENT);
}

void TestSegmentDescriptor::testProtectedModeKernelFlatDataDescriptor(void)
{
    SegmentDescriptor *desc;

    desc = SegmentDescriptor::aDataSegmentDescriptor()
       ->withBaseAddress(0u)
       ->withLimit(0xFFFFF)
       ->withKernelCredential()
       ->withPageGranularity()
       ->markedAsPresent()
       ->for32bitProtectedMode()
       ->withWritePermission();
    TS_ASSERT_EQUALS((uint64_t)desc->toRawSegmentDescriptor(), KERNEL_FLAT_DATA_SEGMENT);
}

void TestSegmentDescriptor::testProtectedModeUserFlatCodeDescriptor(void)
{
    SegmentDescriptor *desc;

    desc = SegmentDescriptor::aCodeSegmentDescriptor()
       ->withBaseAddress(0u)
       ->withLimit(0xFFFFF)
       ->withUserCredential()
       ->withPageGranularity()
       ->markedAsPresent()
       ->for32bitProtectedMode()
       ->withReadPermission();
    TS_ASSERT_EQUALS((uint64_t)desc->toRawSegmentDescriptor(), USER_FLAT_CODE_SEGMENT);
}

void TestSegmentDescriptor::testProtectedModeUserFlatDataDescriptor(void)
{
    SegmentDescriptor *desc;

    desc = SegmentDescriptor::aDataSegmentDescriptor()
       ->withBaseAddress(0u)
       ->withLimit(0xFFFFF)
       ->withUserCredential()
       ->withPageGranularity()
       ->markedAsPresent()
       ->for32bitProtectedMode()
       ->withWritePermission();
    TS_ASSERT_EQUALS((uint64_t)desc->toRawSegmentDescriptor(), USER_FLAT_DATA_SEGMENT);
}
