#ifndef SMATH_H_INCLUDE
#define SMATH_H_INCLUDE

#include <stdint.h>

#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void millisleep(const uint64_t ms);

#endif
