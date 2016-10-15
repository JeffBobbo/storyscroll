#ifndef CONSOLE_H_INCLUDE
#define CONSOLE_H_INCLUDE

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h> // console size stuff
#endif

#include <stdio.h>
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

console_v console_size()
{
  console_v sz = {0, 0};
#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO cinfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
  sz.x = cinfo.srWindow.Right - cinfo.srWindow.Left + 1; // ugly hack: reports 1 less than actual value
  sz.y = cinfo.srWindow.Bottom - cinfo.srWindow.Top + 1; // ditto
#else
  struct winsize ws;
  ioctl(0, TIOCGWINSZ, &ws);

  sz.x = ws.ws_col;
  sz.y = ws.ws_row;
#endif
  return sz;
}

void console_set_colour(console_col col)
{
#ifdef _WIN32
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, WORD(col));
#else
  uint8_t fg = (col & 0x0F);
  uint8_t bg = col >= BG_RED ? (col & 0xF0) / 16 : 0;

  printf("\033[%i;%im", fg + 30, bg + 40); ///*(col & FG_INTENSE ? ";1" : ";24") <<*/ "m";
#endif
}


void console_set_cursor_pos(const int16_t x, const int16_t y)
{
#ifdef _WIN32
  COORD c = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
#else
  printf("\033[%i;%iH", y+1, x+1);
#endif
}
void console_set_cursor_posv(const console_v* const p)
{
  console_set_cursor_pos(p->x, p->y);
}

void console_clear()
{
#ifdef _WIN32
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_SCREEN_BUFFER_INFO cinfo;
  GetConsoleScreenBufferInfo(handle, &cinfo);
  COORD c = {0, 0};
  ConsoleVec s = console_size();
  DWORD junk; // not needed, but required
  FillConsoleOutputCharacter(handle, ' ', s.x * s.y, c, &junk);

  FillConsoleOutputAttribute(handle, cinfo.wAttributes, s.x * s.y, c, &junk); // not sure why this is here fully, but it was on MSDN
#else
  printf("\033[2J"); // clear
#endif
  console_set_cursor_pos(0, 0);
}


void output(const char* const str, const int16_t x, const int16_t y, const console_col c)
{
  if (c >= 0)
    console_set_colour(c);
  if (x >= 0 && y >= 0)
    console_set_cursor_pos(x, y);
  printf("%s", str);
  console_set_colour(FG_DEFAULT|BG_DEFAULT);
}

#endif
