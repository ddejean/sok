#include <stdlib.h>
#include <string.h>
#include "TestGdt.h"
#include "Arch/Gdt.h"


#define TEST_GDT_COUNT     8

/* A raw gdt for test purposes */
static RawSegmentDescriptor testGdt[TEST_GDT_COUNT]
       __attribute__((aligned(8)));

/* The test GDT instance */
static Gdt *gdt;

void TestGdt::setUp(void)
{
    gdt = new Gdt(testGdt, TEST_GDT_COUNT);
}

void TestGdt::tearDown(void)
{
    delete gdt;
    gdt = NULL;
    memset(testGdt, 0, sizeof(testGdt));
}

void TestGdt::testBaseAddress(void)
{
    TS_ASSERT((gdt->getBaseAddress() & 0x7u) == 0u);
}

void TestGdt::testLimit(void)
{
    TS_ASSERT_EQUALS(gdt->getLimit(), sizeof(testGdt) - 1);
}

void TestGdt::testInsert(void)
{
    SegmentDescriptor *nullDesc, *codeDesc, *dataDesc;

    nullDesc = SegmentDescriptor::aNullSegmentDescriptor();
    codeDesc = SegmentDescriptor::aCodeSegmentDescriptor();
    dataDesc = SegmentDescriptor::aDataSegmentDescriptor();

    gdt->insert(0, nullDesc);
    gdt->insert(1, codeDesc);
    gdt->insert(2, dataDesc);
    gdt->insert(3, codeDesc);
    gdt->insert(4, dataDesc);

    TS_ASSERT_EQUALS(testGdt[0], nullDesc->toRawSegmentDescriptor());
    TS_ASSERT_EQUALS(testGdt[1], codeDesc->toRawSegmentDescriptor());
    TS_ASSERT_EQUALS(testGdt[2], dataDesc->toRawSegmentDescriptor());
    TS_ASSERT_EQUALS(testGdt[3], codeDesc->toRawSegmentDescriptor());
    TS_ASSERT_EQUALS(testGdt[4], dataDesc->toRawSegmentDescriptor());

    delete nullDesc;
    delete codeDesc;
    delete dataDesc;
}
