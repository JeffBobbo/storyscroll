#ifndef SCROLL_H_INCLUDE
#define SCROLL_H_INCLUDE

#include <stdint.h>

uint32_t scroll_print_top(const uint32_t width, const uint32_t height, const uint32_t scroll);
uint32_t scroll_print_body(const uint32_t width, const uint32_t height, char* const s, const uint32_t scroll);
uint32_t scroll_print_bottom(const uint32_t width, const uint32_t height, int32_t* d);
#endif
