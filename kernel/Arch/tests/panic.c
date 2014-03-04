#include <execinfo.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static void *backtrace_buffer[32];

void panic(const char *fmt, ...)
{
        va_list args;
        int i, entries;
        void *addr;
        char **symbols;

        /* Print user message */
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);

        /* Get the stack trace */
        memset(backtrace_buffer, 0, 32 * sizeof(void *));
        entries = backtrace(backtrace_buffer, 32);
        symbols = backtrace_symbols(backtrace_buffer, entries);

        /* Print the stack trace */
        printf("\nStack trace:\n");
        for (i = 0; i < entries; ++i) {
                addr = backtrace_buffer[i];
                printf(" %3d: %s(%08x)\n", i, symbols[i], (uintptr_t) addr);
        }
        assert(0 && "Failure. Stop here.");
}
