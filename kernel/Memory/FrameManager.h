/*
 * FrameManager.h
 *
 * Copyright (C) 2013, the Simple Object Kernel project.
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Management class for hardware memory (framebased).
 */

#ifndef _HARDWARE_MEMORY_MANAGER_H_
#define _HARDWARE_MEMORY_MANAGER_H_

#include "Utils/List.h"

class FrameManager {
private:
    /* Size of a physical frame for this manager. */
    unsigned mFrameSize;
    /* The list of free frames.*/
    List<void*> *mFrameList;
    /* Memory boundaries */
    void *mStart;
    void *mEnd;

public:
    FrameManager(void *start, unsigned frameSize, unsigned areaSize);
    ~FrameManager();

    /**
     * Retain a free frame. The frame will be removed from this manager, and
     * freely usable by the system.
     *
     * @return the physical addres of the frame.
     */
    void *frameRetain(void);

    /**
     * Free (give back) a previously retained frame.
     *
     * @pre @frame is aligned on the provided <frameSize>, failure otherwise.
     */
    void frameRelease(void *frame);

    /**
     * Retrieve the number of free frames present in the manager.
     */
    unsigned count(void);

    /**
     * Retrieve the size of a frame.
     */
    unsigned getFrameSize(void);
};

#endif /* _HARDWARE_MEMORY_MANAGER_H_ */
