#ifndef _TESTMATH_H_
#define _TESTMATH_H_

#include "CxxTest/TestSuite.h"
#include "Utils/Math.h"

/**
 * Implements tests for the List<T> template class.
 */
class TestMath : public CxxTest::TestSuite
{
public:
    void testIsPowerOfTwo(void);
    void testUpperPowerOfTwo(void);
};

#endif /* _TESTMATH_H_ */
