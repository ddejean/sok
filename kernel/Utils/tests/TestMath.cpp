#include "TestMath.h"

void TestMath::testIsPowerOfTwo(void)
{
    for (int i = 0; i < 32; i++) {
        TS_ASSERT(Math::isPowerOfTwo(1 << i));
    }

    TS_ASSERT(!Math::isPowerOfTwo(0));
    TS_ASSERT(!Math::isPowerOfTwo(10));
    TS_ASSERT(!Math::isPowerOfTwo(0xFFFFFFFF));
}

void TestMath::testUpperPowerOfTwo(void)
{
    TS_ASSERT_EQUALS(1, Math::upperPowerOfTwo(0));

    for (int i = 0; i < 32; i++) {
        TS_ASSERT_EQUALS(1 << i, Math::upperPowerOfTwo(1 << i));
    }

    for (int i = 2; i < 32; i++) {
        TS_ASSERT_EQUALS(1 << i, Math::upperPowerOfTwo((1 << i) - 1));
    }

    TS_ASSERT_EQUALS(16, Math::upperPowerOfTwo(10));
    TS_ASSERT_EQUALS(32, Math::upperPowerOfTwo(24));
    TS_ASSERT_EQUALS(256, Math::upperPowerOfTwo(255));
}
