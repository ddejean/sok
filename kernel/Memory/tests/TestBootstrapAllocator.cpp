#include "TestBootstrapAllocator.h"
#include <string.h>
#include <stdint.h>

void TestBootstrapAllocator::setUp(void)
{
    BootstrapAllocator::reset();
}

void TestBootstrapAllocator::testSingleton(void)
{
    BootstrapAllocator *a1, *a2;

    a1 = BootstrapAllocator::getInstance();
    TS_ASSERT_DIFFERS(a1, (void*)NULL);
    a2 = BootstrapAllocator::getInstance();
    TS_ASSERT_DIFFERS(a2, (void*)NULL);

    TS_ASSERT_EQUALS(a1, a2);
}

void TestBootstrapAllocator::testReset(void)
{
    uint32_t *chunk;
    BootstrapAllocator *ba;

    ba = BootstrapAllocator::getInstance();
    TS_ASSERT_DIFFERS(ba, (void*)NULL);

    chunk = (uint32_t*) ba->alloc(32);
    TS_ASSERT_DIFFERS(chunk, (void*)NULL);
    *chunk = 0xDEADBEEFu;

    BootstrapAllocator::reset();
    TS_ASSERT_DIFFERS(*chunk, 0xDEADBEEFu);

    chunk = (uint32_t*) ba->alloc((uint32_t) ba->heapSize());
    TS_ASSERT_DIFFERS(chunk, (void*)NULL);
}

