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
  const console_v csz = console_size();

  printf("Console size: %ix%i\n", csz.x, csz.y);
  getc(stdin);

  uint32_t i = 70;
  while (!sigC)
  {
    int32_t space = MIN(csz.y, i); // how much space we have to use. space <= used
    int32_t used = 0; // how much space have we used so far
    int32_t offset = csz.y - i; // how much are we offset, 0 is the top of the console

    console_clear();
    if (offset > 0) // if so, move the cursor to the right place so we scroll up
    {
      //used = csz.y - i;
      console_set_cursor_pos(0, offset);
    }
    used += scroll_print_top(csz.x, space, used, offset);
    used += scroll_print_body(csz.x, space, used, offset, story);
    int32_t d = 0;
    used += scroll_print_bottom(csz.x, space, used, offset, &d);
    //printf("%i\n", used);
    fflush(stdout);
    millisleep(1000);
    ++i;
    if (d)
      break;
  }
  if (!sigC)
    getc(stdin); // really bad, but whatever
  console_clear();
  return 0;
}
