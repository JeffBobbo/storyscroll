#ifndef SMATH_H_INCLUDE
#define SMATH_H_INCLUDE

#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h> // nanosleep
#else
#include <unistd.h> // usleep
#endif


#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void millisleep(const uint64_t ms);

#endif
