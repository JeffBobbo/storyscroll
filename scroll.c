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

char* next_line(const char* const s, uint32_t reset)
{
  static char* str = NULL;
  static uint32_t lines = 0;
  static uint32_t progress = 0;
  static size_t* linepos = NULL;
  if ((s && str != s) || reset)
  {
    str = (char*)s;
    lines = 0;
    free(linepos);
    for (uint32_t i = 0, l = strlen(str); i < l; ++i)
    {
      if (str[i] == '\n')
        ++lines;
    }
    linepos = malloc(sizeof(size_t) * lines*2);
    linepos[0] = 0;
    size_t i = 0, l = strlen(str), j = 1;
    for (; i < l; ++i)
    {
      if (str[i] == '\n')
      { 
        linepos[j++] = i;
        linepos[j++] = i+1;
      }
    }
    linepos[j] = l;
    progress = 0;
    return NULL;
  }

  if (progress >= lines*2)
    return NULL;
  size_t start = linepos[progress++];
  size_t end = linepos[progress++];
  size_t len = end-start;
  char* ret = malloc(sizeof(char) * (len+1));
  memcpy(ret, str+start, len);
  ret[len] = '\0';
  return ret;
}

const char* const SCROLL_LEFT = "                         @@  ";
const char* const SCROLL_RIGHT = "         @@                         ";
uint32_t scroll_print_body(const uint32_t width, const uint32_t height, char* const s, const uint32_t scroll)
{
  uint32_t SCROLL_LEFT_W = strlen(SCROLL_LEFT);
  uint32_t SCROLL_RIGHT_W = strlen(SCROLL_RIGHT);

  char* line = next_line(s, 1);
  uint32_t i = scroll;
  for (; i < height; ++i)
  {
    line = next_line(s, 0);
    if (!line)
      break;
    const uint32_t lineLen = strlen(line);
    for (size_t sz = 0; sz < lineLen; ++sz)
    {
      if (line[sz] == '\n')
        line[sz] = '%';
    }
    // TODO: Check if the line is too long
    printf("%s%s", SCROLL_LEFT, line);
    for (uint32_t j = 0; j < width - (SCROLL_LEFT_W + SCROLL_RIGHT_W + lineLen); ++j)
      printf(" ");
    printf("%s\n", SCROLL_RIGHT);
  }
  return i - scroll;
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
