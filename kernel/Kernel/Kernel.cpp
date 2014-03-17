/*
 * kernel.cpp
 *
 * Copyright (C) 2012-2013 Simple Object Kernel project
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * C++ kernel entry point.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "assert.h"
#include "Kernel.h"
#include "Runtime/runtime.h"
#include "Memory/BootstrapAllocator.h"
#include "Arch/Cpu.h"
#include "Arch/SokGdt.h"


void kernel_main(struct boot_context *context, int argc, char **argv)
{
        (void)argc;
        (void)argv;
        Cpu *cpu;
        Gdt *gdt;

        printf("%s\n", "Running stage 2 ...");
        assert(context != NULL);

        /* Prepare runtime environment */
        runtime_init();
        runtime_inject_allocator(BootstrapAllocator::getInstance());

        /* Setup processor */
        gdt = SokGdt::theKernelGdt();
        cpu = Cpu::aCpu();
        cpu->withGdtAndSegments(gdt, KERNEL_CS, KERNEL_DS);

}


#ifdef __cplusplus
}
#endif

