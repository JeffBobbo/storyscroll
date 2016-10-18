#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "story.h"
#include "scroll.h"
#include "smath.h"
#include "term/console.h"

static volatile uint32_t sigC = 0;

void int_handler(int dummy)
{
  sigC = 1;
}

void millisleep(const uint64_t ms)
{
#ifdef _WIN32
  Sleep(ms);
#elif _POSIX_C_SOURCE >= 199309L
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  struct timespec rem = {0, 0};
  //do
  {
    nanosleep(&ts, &rem);
  }
  //while (rem.tv_sec || rem.tv_nsec);
#else
  usleep(ms * 1000);
#endif
}

int main(int argc, char const** argv)
{
  char storyFile[80] = "story.txt";

  if (argc > 1)
    strcpy(storyFile, argv[1]);

  char* story = readfile(storyFile);

  if (!story)
  {
    printf("No story found!\n");
    return 1;
  }

  signal(SIGINT, int_handler);

  // how much space do we have to play with?
  console_v csz = console_size();

  uint32_t i = 0;
  while (!sigC)
  {
    uint32_t printed = 0; // how much space have we used
    uint32_t toPrint = MIN(csz.y, i);
    console_clear();
    if (i < csz.y) // if so, move the cursor to the right place so we scroll up
      console_set_cursor_pos(0, csz.y - i);

    uint32_t scroll = MAX((int32_t)i - csz.y, 0);
//    printed += scroll_print_top(csz.x, toPrint, scroll);
    printed += scroll_print_body(csz.x, csz.y - (i + printed), story);
    int32_t d = 0;
    //printed += scroll_print_bottom(csz.x, toPrint - printed, &d);
    //printf("%i\n", printed);
    fflush(stdout);
    millisleep(500);
    ++i;
    if (d)
      break;
  }
  if (!sigC)
    getc(stdin); // really bad, but whatever
  console_clear();
  return 0;
}
