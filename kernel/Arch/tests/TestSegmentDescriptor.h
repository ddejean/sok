#ifndef _TESTSEGMENTDESCRIPTOR_H_
#define _TESTSEGMENTDESCRIPTOR_H_

#include "CxxTest/TestSuite.h"

class TestSegmentDescriptor: public CxxTest::TestSuite {
    public:
        void testNullDescriptor(void);
        void testProtectedModeKernelFlatCodeDescriptor(void);
        void testProtectedModeKernelFlatDataDescriptor(void);
        void testProtectedModeUserFlatCodeDescriptor(void);
        void testProtectedModeUserFlatDataDescriptor(void);
};

#endif /* _TESTSEGMENTDESCRIPTOR_H_ */
