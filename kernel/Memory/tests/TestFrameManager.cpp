#include "TestFrameManager.h"

void TestFrameManager::setUp(void)
{
    mFrameManager = new FrameManager(START,                     /* 0x10000 */
                                     FRAME_SIZE,                /* 4 KB */
                                     FRAME_SIZE * FRAME_COUNT); /* 3*4 KB */
}

void TestFrameManager::tearDown(void)
{
    delete mFrameManager;
    mFrameManager = NULL;
}

void TestFrameManager::testInitialParameters(void)
{
    TS_ASSERT(mFrameManager != NULL);
    TS_ASSERT_EQUALS(FRAME_COUNT, mFrameManager->count());
    TS_ASSERT_EQUALS(FRAME_SIZE, mFrameManager->getFrameSize());
}

void TestFrameManager::testFrameRetain(void)
{
    void *frames[FRAME_COUNT];

    for (unsigned i = 0; i < FRAME_COUNT; i++) {
        frames[i] = mFrameManager->frameRetain();
        TS_ASSERT_DIFFERS((void*)0, frames[i]);
        TS_ASSERT_LESS_THAN((unsigned)frames[i], (unsigned)END);
        TS_ASSERT_LESS_THAN_EQUALS((unsigned)START, (unsigned)frames[i]);
    }

    TS_ASSERT_EQUALS((void*)0, mFrameManager->frameRetain());
    TS_ASSERT_EQUALS(0, mFrameManager->count());
}

void TestFrameManager::testFrameRelease(void)
{
    void *frames[FRAME_COUNT];
    void *aFrame;
    unsigned i;

    for (i = 0; i < FRAME_COUNT; i++) {
        frames[i] = mFrameManager->frameRetain();
    }

    TS_ASSERT_EQUALS((void*)0, mFrameManager->frameRetain());
    TS_ASSERT_EQUALS(0, mFrameManager->count());

    aFrame = frames[0];
    frames[0] = NULL;
    mFrameManager->frameRelease(aFrame);
    TS_ASSERT_EQUALS(1, mFrameManager->count());
    frames[0] = mFrameManager->frameRetain();
    TS_ASSERT_EQUALS(aFrame, frames[0]);

    for (i = 0; i < FRAME_COUNT; i++) {
        mFrameManager->frameRelease(frames[i]);
        TS_ASSERT_EQUALS(i + 1, mFrameManager->count());
    }
}

