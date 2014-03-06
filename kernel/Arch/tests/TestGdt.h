#ifndef _TESTGDT_H_
#define _TESTGDT_H_

#include "CxxTest/TestSuite.h"

class TestGdt: public CxxTest::TestSuite {
    public:
        void setUp(void);
        void tearDown(void);

        void testBaseAddress(void);
        void testLimit(void);
        void testInsert(void);
};

#endif /* _TESTGDT_H_ */
