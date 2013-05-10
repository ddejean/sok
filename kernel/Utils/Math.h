/*
 * Math.h
 *
 * Copyright (C) 2013, the Simple Object Kernel project.
 * by Damien Dejean <dam.dejean@gmail.com>
 *
 * Small math library.
 */

#ifndef _MATH_H_
#define _MATH_H_

#include <assert.h>

class Math
{
public:
    /**
     * Tells if a number is a power of two.
     * @param value the number to test.
     * @return true if value is a power of two.
     */
    static inline bool isPowerOfTwo(unsigned value)
    {
        return (value != 0u) && ((value & (value - 1)) == 0u);
    }

    /**
     * Get the upper power of two of a number.
     * @param value the initial value to get the power from.
     * @return the upper power of two from value.
     */
    static inline unsigned upperPowerOfTwo(unsigned value)
    {
        /* Implemented only with 32 bits integers */
        assert(sizeof(value) == 4);

        if (value == 0) return 1;

        value--;
        value = value | (value >> 1);
        value = value | (value >> 2);
        value = value | (value >> 4);
        value = value | (value >> 8);
        value = value | (value >> 16);
        value++;

        return value;
    }
};

#endif /* _MATH_H_ */
