/*
 * Cpu.cpp
 *
 * Copyright (C) 2014 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * CPU standard operations implementation.
 */

#include <assert.h>
#include <stddef.h>
#include "Cpu.h"

Cpu::Cpu(void)
{
}

Cpu* Cpu::withGdtAndSegments(Gdt *gdt, uint16_t CS, uint16_t DS)
{
    assert(gdt != NULL);


    mGdt = gdt;

    mGdtR.limit = gdt->getLimit();
    mGdtR.base  = gdt->getBaseAddress();

    /* Load GDT register */
    __asm__ __volatile__("lgdt  %0" : : "m" (mGdtR.limit), "m" (mGdtR.base));

    /* Update data segments */
    __asm__ __volatile__ ("movw     %w0, %%ss" : : "r" (DS));
    __asm__ __volatile__ ("movw     %w0, %%ds" : : "r" (DS));
    __asm__ __volatile__ ("movw     %w0, %%es" : : "r" (DS));
    __asm__ __volatile__ ("movw     %w0, %%fs" : : "r" (DS));
    __asm__ __volatile__ ("movw     %w0, %%gs" : : "r" (DS));

    /*
     * Update code segment.
     * As ljmp instruction only supports immediate values as segment descriptor,
     * we case the segment value to run the correct instruction.
     */
    switch (CS) {
        case 0x08:
            __asm__ __volatile__ ("ljmp $0x08,  $0f\n 0:");
            break;
        case 0x10:
            __asm__ __volatile__ ("ljmp $0x10,  $0f\n 0:");
            break;
        case 0x18:
            __asm__ __volatile__ ("ljmp $0x18,  $0f\n 0:");
            break;
        case 0x20:
            __asm__ __volatile__ ("ljmp $0x20,  $0f\n 0:");
            break;
        case 0x28:
            __asm__ __volatile__ ("ljmp $0x28,  $0f\n 0:");
            break;
        case 0x30:
            __asm__ __volatile__ ("ljmp $0x30,  $0f\n 0:");
            break;
        case 0x38:
            __asm__ __volatile__ ("ljmp $0x38,  $0f\n 0:");
            break;
        default:
            assert(0 && "Unsupported segment value !");
    };

    /* Everything is up to date, leave ;) */
    return this;
}

Cpu* Cpu::aCpu(void)
{
    return new Cpu();
}
