#include "scroll.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "smath.h"

const char* const SCROLL_TOP_LEFT[] = {
"                                  :@@@@@@@@@@@@@@@@@@@",
"                               `#@@@@@@@@@@@@@@@@@@@@@",
"                              '@@@'.     .+@@@,       ",
"                             #@@;           #@@;      ",
"                            @@@`             .@@;     ",
"                           +@@                .@@.    ",
"                          `@@                  :@@    ",
"                          #@'                   #@;   ",
"                          @@                    `@@   ",
"                         ;@+                     @@   ",
"                         #@`                     +@;  ",
"                         @@                      ,@+  ",
"                         @@        ;@@@@@@@@@@@@@@@#  ",
"                         @@      `@@@@@@@@@@@@@@@@@#  ",
"                         @@     `@@#`            :@+  ",
"                         @@     @@'              #@:  ",
"                         @@    ,@@               @@   ",
"                         @@    +@,              ,@@   ",
"                         @@    #@               @@.   ",
"                         @@    #@              '@@    ",
"                         @@    '@'            ;@@`    ",
"                         @@    `@@           +@@.     ",
"                         @@     #@@        ,@@@.      ",
"                         @@      @@@'   `+@@@@        ",
"                         @@       #@@@@@@@@@@@@@@@@@@@",
"                         @@         '#@@@@@@@@@@@@@@@@"};

const char* const SCROLL_TOP_RIGHT[] = {
"@@+.         ",
"@@@@@;       ",
"  ,@@@@`     ",
"    `@@@.    ",
"      '@@.   ",
"       ;@@   ",
"        +@#  ",
"         @@. ",
"         :@# ",
"          @@ ",
"          @@`",
"          '@,",
"          '@:",
"          '@,",
"          +@.",
"          @@`",
"          @@ ",
"         '@+ ",
"         @@` ",
"        @@'  ",
"       #@@   ",
"      #@@    ",
"    ;@@@     ",
" .#@@@#      ",
"@@@@@        ",
"#+,          "};


uint32_t scroll_print_top(const uint32_t width, const uint32_t height, const uint32_t scroll)
{
  uint32_t SCROLL_TOP_LEFT_W = strlen(SCROLL_TOP_LEFT[0]);
  uint32_t SCROLL_TOP_RIGHT_W = strlen(SCROLL_TOP_RIGHT[0]);

  const uint32_t MIDDLE_WIDTH = width - SCROLL_TOP_LEFT_W - SCROLL_TOP_RIGHT_W;
  const uint32_t h = MIN(sizeof(SCROLL_TOP_LEFT) / sizeof(SCROLL_TOP_LEFT[0]), height);
  uint32_t i = scroll;
  for (; i < h; ++i)
  {
    if (i != scroll)
      printf("\n");
    printf("%s", SCROLL_TOP_LEFT[i]);
    for (uint32_t j = 0; j < MIDDLE_WIDTH; ++j)
      printf(i <= 1 || i >= 24 ? "@" : " ");
    printf("%s", SCROLL_TOP_RIGHT[i]);
  }
  return i;
}

const char* const SCROLL_LEFT = "                         @@  ";
const char* const SCROLL_RIGHT = "         @@";
uint32_t scroll_print_body(const uint32_t width, const uint32_t height, char* const s)
{
  char* story = malloc(sizeof(char) * strlen(s));
  strcpy(story, s);
  uint32_t SCROLL_LEFT_W = strlen(SCROLL_LEFT);
  uint32_t SCROLL_RIGHT_W = strlen(SCROLL_RIGHT);

  static uint32_t lines = 0;
  static uint32_t progress = 0;
  // count the number of lines
  if (!lines)
  {
    for (uint32_t i = 0, l = strlen(story); i < l; ++i)
    {
      if (story[i] == '\n')
        ++lines;
    }
  }

  uint32_t toDo = MIN(lines, height);

  char* line = strtok(story, "\n");
  for (uint32_t i = 1; i < progress; ++i)
    line = strtok(NULL, "\n");

  // logic here for determinating which lines to print is broken
  for (uint32_t i = 0; i < toDo && line; ++i)
  {
    const uint32_t lineLen = strlen(line);
    // TODO: Check if the line is too long
    printf("%s%s", SCROLL_LEFT, line);
    for (uint32_t j = 0; j < width - SCROLL_LEFT_W - SCROLL_RIGHT_W - lineLen-1; ++j)
      printf(" ");
    printf("%s\n", SCROLL_RIGHT);
    line = strtok(NULL, "\n");
    ++progress;
  }
  return toDo;
}



const char* const SCROLL_BOTTOM_LEFT[] = {
"         `:#@@@@@@@@@@@@@@@  ",
"       .@@@@@@@@@@@@@@@@@@@  ",
"      #@@@'.   ,@@@      @@  ",
"    `@@@,        #@@     @@  ",
"   `@@#           @@,    @@  ",
"   @@+            .@#    @@  ",
"  #@#              @@    @@  ",
" `@@               @@    @@  ",
" @@:              .@@    @@  ",
" @@               #@:    @@  ",
" @#              ;@@     @@  ",
";@'             #@@.     @@  ",
"+@:         @@@@@@@@@@@@@@@  ",
"+@:         @@@@@@@@@@@@@@@  ",
";@'                      @@  ",
"`@#                     `@@  ",
" @@                     :@'  ",
" @@,                    @@.  ",
" .@@                   ,@@   ",
"  @@'                  @@.   ",
"  `@@,                @@+    ",
"   ,@@;             `@@@     ",
"    ,@@#`          ;@@@      ",
"     `@@@#:     `+@@@'       ",
"       ;@@@@@@@@@@@@@@@@@@@@@",
"         `#@@@@@@@@@@@@@@@@@@"
};
const char* const SCROLL_BOTTOM_RIGHT[] = {
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @@                         ",
"         @#                         ",
"        ,@+                         ",
"        @@,                         ",
"        @@                          ",
"       +@+                          ",
"      .@@                           ",
"     `@@:                           ",
"    .@@+                            ",
"   +@@+                             ",
".+@@@:                              ",
"@@@#                                ",
"#,                                  "
};

uint32_t scroll_print_bottom(const uint32_t width, const uint32_t height, int32_t* d)
{
  uint32_t SCROLL_BOTTOM_LEFT_W = strlen(SCROLL_BOTTOM_LEFT[0]);
  uint32_t SCROLL_BOTTOM_RIGHT_W = strlen(SCROLL_BOTTOM_RIGHT[0]);

  const uint32_t MIDDLE_WIDTH = width - SCROLL_BOTTOM_LEFT_W - SCROLL_BOTTOM_RIGHT_W;
  const uint32_t HEIGHT = sizeof(SCROLL_BOTTOM_LEFT) / sizeof(SCROLL_BOTTOM_LEFT[0]);
  const uint32_t h = MIN(HEIGHT, height);
  uint32_t i;
  for (i = 0; i < h; ++i)
  {
    if (i)
      printf("\n");
    printf("%s", SCROLL_BOTTOM_LEFT[i]);
    for (uint32_t j = 0; j < MIDDLE_WIDTH; ++j)
      printf(i >= 24 ? "@" : " ");
    printf("%s", SCROLL_BOTTOM_RIGHT[i]);
  }
  if (i == HEIGHT)
    *d = 1;
  return i;
}
