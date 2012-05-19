#include "assert.h"
#include "backtrace.h"
#include "stdarg.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#ifndef MAX_STACK_TRACE_DEPTH
#define MAX_STACK_TRACE_DEPTH 15
#endif

static void *backtrace_buffer[MAX_STACK_TRACE_DEPTH];

__inline__ static void hlt(void)
{
	__asm__ __volatile__("hlt");
}

void panic(const char *fmt, ...)
{
        va_list args;
        int i, max;
        void *addr;

        /* Print user message */
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);

        /* Get the stack trace */
        memset(backtrace_buffer, 1, MAX_STACK_TRACE_DEPTH * sizeof(void *));
        max = backtrace(backtrace_buffer, MAX_STACK_TRACE_DEPTH);

        /* Print the stack trace */
        printf("\nstack trace:\n");
        for (i = 0; i < max; ++i) {
                addr = backtrace_buffer[i];
                printf(" %3d: %08x\n", i, (uintptr_t) addr);
        }

        /* Stop here... */
        printf("\nkernel halted!");
        while (1) {
                hlt();
        }
}



