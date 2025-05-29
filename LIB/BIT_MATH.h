#ifndef BIT_MATH_H
#define BIT_MATH_H

// Macro to set a specific bit in a variable
#define SET_BIT(NUM, BIT_NUM) ((NUM) |= (1u << (BIT_NUM)))

// Macro to clear (reset) a specific bit in a variable
#define CLR_BIT(NUM, BIT_NUM) ((NUM) &= ~(1u << (BIT_NUM)))

// Macro to toggle (invert) a specific bit in a variable
#define TOG_BIT(NUM, BIT_NUM) ((NUM) ^= (1u << (BIT_NUM)))

// Macro to get the value of a specific bit in a variable
#define GET_BIT(NUM, BIT_NUM) (((NUM) >> (BIT_NUM)) & 1u)



#endif