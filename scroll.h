#ifndef SCROLL_H_INCLUDE
#define SCROLL_H_INCLUDE

#include <stdint.h>

uint32_t scroll_print_top(const int32_t width, const int32_t space, const int32_t used, const int32_t offset);
uint32_t scroll_print_body(const int32_t width, const int32_t space, const int32_t used, const int32_t offset, char* const s);
uint32_t scroll_print_bottom(const int32_t width, const int32_t space, const int32_t used, const int32_t offset, int32_t* const d);
#endif
