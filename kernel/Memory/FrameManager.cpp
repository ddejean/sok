/*
 * FrameManager.cpp
 *
 * Copyright (C) 2013, the Simple Object Kernel project.
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Implementation of management class for hardware memory (framebased).
 */

#include <assert.h>
#include "FrameManager.h"
#include "Utils/LinkedList.h"
#include "Utils/Math.h"

FrameManager::FrameManager(void *start, unsigned frameSize, unsigned areaSize)
{
    unsigned frameSizeMask;

    /* Some check on provided values */
    assert(frameSize != 0u);
    assert(Math::isPowerOfTwo(frameSize));
    frameSizeMask = frameSize - 1;
    /* At least one frame */
    assert((areaSize & ~frameSizeMask) > 0u);
    /* An entire number of frames */
    assert((areaSize & frameSizeMask) == 0u);
    /* The given address is aligned on a frame */
    assert(((unsigned)start & frameSizeMask) == 0);

    mFrameSize = frameSize;
    mStart = start;
    mEnd = (void*)((unsigned)start + areaSize);
    mFrameList = new LinkedList<void*>();
    assert(mFrameList != NULL);

    /* Fill the list of free frames */
    for (char *address = (char*) mStart;
         (unsigned)address < (unsigned)mEnd;
         address += mFrameSize) {
        mFrameList->append(address);
    }

    assert(mFrameList->count() * mFrameSize == areaSize);
}

FrameManager::~FrameManager()
{
    delete mFrameList;
    mFrameList = NULL;
    mFrameSize = 0u;
}

void *FrameManager::frameRetain(void)
{
    void *address = NULL;

    assert(mFrameList != NULL);

    if (!mFrameList->isEmpty()) {
        address = mFrameList->at(0);
        mFrameList->removeAt(0);
    }

    return address;
}

void FrameManager::frameRelease(void *frame)
{
    assert(mFrameList != NULL);
    assert(frame != NULL);
    assert((unsigned)frame >= (unsigned)mStart);
    assert((unsigned)frame < (unsigned)mEnd);

    mFrameList->append(frame);
}

unsigned FrameManager::count(void)
{
    assert(mFrameList != NULL);
    return mFrameList->count();
}

unsigned FrameManager::getFrameSize(void)
{
    assert(mFrameList != NULL);
    return mFrameSize;
}

