#include <stdio.h>
#include <string.h>

#include "story.h"

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

  const int SCROLL_WIDTH = 66;
  //const int SCROLL_HEIGHT = 24;

  printf("  ______                                                                   ______\n");
  printf(" /     /__________________________________________________________________/     / \n");
  printf("|     |                                                                  |     |\n");

  char* line = strtok(story, "\n");
  do
  {
    printf("|     |%s", line);
    for (int i = 0, l = SCROLL_WIDTH - strlen(line); i < l; ++i)
      printf(" ");
    printf("|     |\n");
  }
  while ((line = strtok(NULL, "\n")) && strlen(line));

  printf("|     |__________________________________________________________________|     |\n");
  printf("/____/                                                                  /_____/ \n");

  return 0;
}