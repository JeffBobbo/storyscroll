#include <stdio.h>
#include <string.h>

#include "story.h"
#include "scroll.h"
#include "smath.h"
#include "term/console.h"


void millisleep(const uint64_t ms)
{
#ifdef _WIN32
  Sleep(ms);
#elif _POSIX_C_SOURCE >= 199309L
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  struct timespec rem = {0, 0};
  do
  {
    nanosleep(&ts, &rem);
  }
  while (rem.tv_sec || rem.tv_nsec);
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

  // how much space do we have to play with?
  console_v csz = console_size();

  uint32_t i = 0;
  while (1)
  {
    uint32_t printed = 0; // how much space have we used
    uint32_t toPrint = MIN(csz.y, i);
    console_clear();
    if (i < csz.y)
      console_set_cursor_pos(0, csz.y - i);

    printed += scroll_print_top(csz.x, toPrint);
    printed += scroll_print_bottom(csz.x, toPrint - printed);
    //printf("%i\n", printed);
    fflush(stdout);
    millisleep(100);
    ++i;
  }

  console_clear();
  /*
  char* line = strtok(story, "\n");
  do
  {
    printf("|     |%s", line);
    for (int i = 0, l = SCROLL_WIDTH - strlen(line); i < l; ++i)
      printf(" ");
    printf("|     |\n");
  }
  while ((line = strtok(NULL, "\n")) && strlen(line));
  */
  return 0;
}
