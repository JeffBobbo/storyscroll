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


uint32_t scroll_print_top(const int32_t width, const int32_t space, const int32_t used, const int32_t offset)
{
  int32_t SCROLL_TOP_LEFT_W = strlen(SCROLL_TOP_LEFT[0]);
  int32_t SCROLL_TOP_RIGHT_W = strlen(SCROLL_TOP_RIGHT[0]);

  const int32_t MIDDLE_WIDTH = width - SCROLL_TOP_LEFT_W - SCROLL_TOP_RIGHT_W;

  const int32_t h = MIN(sizeof(SCROLL_TOP_LEFT) / sizeof(SCROLL_TOP_LEFT[0]), (uint32_t)space);
  int32_t i = offset < 0 ? -offset : 0;
  uint32_t p = 0;
  for (; i < h; ++i)
  {
    if (i < 0)
      continue;
    ++p;
    if (i != offset)
      printf("\n");
    printf("%s", SCROLL_TOP_LEFT[i]);
    for (int32_t j = 0; j < MIDDLE_WIDTH; ++j)
      printf(i <= 1 || i >= 24 ? "@" : " ");
    printf("%s", SCROLL_TOP_RIGHT[i]);
  }
  return p;
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
uint32_t scroll_print_body(const int32_t width, const int32_t space, const int32_t used, const int32_t offset, char* const s)
{
  int32_t SCROLL_LEFT_W = strlen(SCROLL_LEFT);
  int32_t SCROLL_RIGHT_W = strlen(SCROLL_RIGHT);

  char* line = next_line(s, 1);

  const int32_t h = space - used;
  int32_t i = 0;//offset+used;
  uint32_t p = 0;
  for (; i < h; ++i)
  {
    line = next_line(s, 0);
    if (i < 0)
      continue;
    if (!line)
      break;
    ++p;
    const size_t lineLen = strlen(line);
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
  return p;
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

uint32_t scroll_print_bottom(const int32_t width, const int32_t space, const int32_t used, const int32_t offset, int32_t* const d)
{
  int32_t SCROLL_BOTTOM_LEFT_W = strlen(SCROLL_BOTTOM_LEFT[0]);
  int32_t SCROLL_BOTTOM_RIGHT_W = strlen(SCROLL_BOTTOM_RIGHT[0]);

  const int32_t MIDDLE_WIDTH = width - SCROLL_BOTTOM_LEFT_W - SCROLL_BOTTOM_RIGHT_W;

  const int32_t h = MIN(sizeof(SCROLL_BOTTOM_LEFT) / sizeof(SCROLL_BOTTOM_LEFT[0]), (uint32_t)(space - used));
  int32_t i = offset < 0 ? -offset: 0;
  uint32_t p = 0;
  for (; i < h; ++i)
  {
    if (i < 0)
      continue;
    ++p;
    if (i)
      printf("\n");
    printf("%s", SCROLL_BOTTOM_LEFT[i]);
    for (int32_t j = 0; j < MIDDLE_WIDTH; ++j)
      printf(i >= 24 ? "@" : " ");
    printf("%s", SCROLL_BOTTOM_RIGHT[i]);
  }
  //if (p == (uint32_t)h)
  //  *d = 1;
  return p;
}
