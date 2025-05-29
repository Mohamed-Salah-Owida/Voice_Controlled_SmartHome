/*
 * MAP.c
 *
 * Created on: Jan 23, 2025
 * Author: moham
 */

#include "STD_TYPES.h"
#include "Map.h"

// Improved Map function
uint16 Map(uint16 Input_Value, uint16 inputRangeMin, uint16 inputRangeMax, uint16 OutputRangeMin, uint16 OutputRangeMax)
{
    // Handle edge case: input range is zero
    if (inputRangeMin == inputRangeMax)
    {
        return OutputRangeMin;
    }

    // Perform the mapping calculation using uint32_t to avoid overflow
    uint32 result = (uint32)(Input_Value - inputRangeMin) * (OutputRangeMax - OutputRangeMin) / (inputRangeMax - inputRangeMin) + OutputRangeMin;

    // Clamp the result to the output range
    if (result < OutputRangeMin)
    {
        result = OutputRangeMin;
    }
    else if (result > OutputRangeMax)
    {
        result = OutputRangeMax;
    }

    return (uint16)result;
}

