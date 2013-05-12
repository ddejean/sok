#ifndef TESTFRAMEMANAGER_H_
#define TESTFRAMEMANAGER_H_

#include "CxxTest/TestSuite.h"
#include "Memory/FrameManager.h"

/* Tests initial parameters */
#define START       ((void*)0x10000)
#define FRAME_SIZE  (0x1000u)
#define FRAME_COUNT (3u)
#define END         ((void*)((unsigned)START + FRAME_SIZE * FRAME_COUNT))


class TestFrameManager: public CxxTest::TestSuite {
private:
    /* The manager we're gonna use for tests */
    FrameManager* mFrameManager;

public:
    void setUp(void);
    void tearDown(void);

    void testInitialParameters(void);
    void testFrameRetain(void);
    void testFrameRelease(void);
};

#endif /* TESTBUDDYALLOCATOR_H_ */
