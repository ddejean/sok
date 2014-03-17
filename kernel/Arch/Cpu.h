/*
 * Cpu.h
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * CPU representation that provides standard operations.
 */

#ifndef _CPU_H_
#define _CPU_H_

#include "Gdt.h"

class Cpu {
private:
    Gdt* mGdt;

    /* For builder use only */
    Cpu(void);

    /*
     * Specific register descriptions.
     */

    struct gdtr {           /* Global descriptor table register */
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed));

    /*
     * Registers declarations.
     */

    struct gdtr mGdtR;

public:
    /**
     * Setup a GDT for the running CPU and updates segments.
     * @param gdt tthe GDT to set up
     *
     * @note expects kernel CS and DS to be 0x8 and 0x10.
     */
    Cpu* updateGdt(Gdt *gdt, uint16_t CS, uint16_t DS);
    /**
     * Provides a CPU instance.
     */
    static Cpu* aCpu(void);
};

#endif /* _CPU_H_ */
