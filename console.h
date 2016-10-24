#ifndef CONSOLE_H_INCLUDE
#define CONSOLE_H_INCLUDE

#include <stdint.h>

// some reference information
// http://en.wikipedia.org/wiki/ANSI_escape_code#CSI_codes


typedef struct console_v
{
  uint16_t x;
  uint16_t y;
} console_v;

typedef enum console_col
{
  NONE = -0x01,
  FG_BLACK  = 0x00,
#ifdef _WIN32
// windows colours
  FG_BLUE   = 0x01,
  FG_GREEN  = 0x02,
  FG_RED    = 0x04,
  BG_BLUE   = 0x10,
  BG_GREEN  = 0x20,
  BG_RED    = 0x40,
  FG_DEFAULT = 0x00,
  BG_DEFAULT = 0x0F,
#else
// linux colours
  FG_RED     = 0x01,
  FG_GREEN   = 0x02,
  FG_BLUE    = 0x04,

  BG_RED     = 0x10,
  BG_GREEN   = 0x20,
  BG_BLUE    = 0x40,

  FG_DEFAULT = 0x09,
  BG_DEFAULT = 0x90,
#endif
  //FG_INTENSE= 0x08,
  //BG_INTENSE= 0x80,
  // convenience
  FG_CYAN    = FG_BLUE|FG_GREEN,
  FG_YELLOW  = FG_GREEN|FG_RED,
  FG_MAGENTA = FG_BLUE|FG_RED,
  FG_WHITE   = FG_BLUE|FG_GREEN|FG_RED,

  BG_CYAN    = BG_BLUE|BG_GREEN,
  BG_YELLOW  = BG_GREEN|BG_RED,
  BG_MAGENTA = BG_BLUE|BG_RED,
  BG_WHITE   = BG_BLUE|BG_GREEN|BG_RED
} console_col;

console_v console_size();
void console_set_colour(console_col col);
void console_set_cursor_pos(const int16_t x, const int16_t y);
void console_set_cursor_posv(const console_v* const p);
void console_clear();
void output(const char* const str, const int16_t x, const int16_t y, const console_col c);

#endif
