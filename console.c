#include "console.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h> // console size stuff
#endif

#include <stdio.h>
#include <stdint.h>

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

  printf("\033[%i;%im", fg + 30, bg + 40);
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
