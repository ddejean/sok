#ifndef TESTBOOTSTRAPALLOCATOR_H_
#define TESTBOOTSTRAPALLOCATOR_H_

#include "CxxTest/TestSuite.h"
#include "Memory/BootstrapAllocator.h"

class TestBootstrapAllocator: public CxxTest::TestSuite {
    public:
        void setUp(void);

        void testSingleton(void);
        void testReset(void);
};

#endif /* TESTBUDDYALLOCATOR_H_ */
