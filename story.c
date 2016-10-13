#include "story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openfile(const char* const filename, const char* const mode)
{
  FILE* f = fopen(filename, mode);
  if (!f)
    fprintf(stderr, "Failed to open `%s` in mode %s\n", filename, mode);
  return f; 
}

char* readfile(const char* const filename)
{
  FILE* f = openfile(filename, "r");
  if (!f)
    return NULL;

  if (fseek(f, 0L, SEEK_END) != 0)
    return NULL;

  int bufsize = ftell(f);
  if (bufsize == -1)
    return NULL;

  char* buf = malloc(sizeof(char) * (bufsize+1));
  fseek(f, 0L, SEEK_SET);

  size_t newlen = fread(buf, sizeof(char), bufsize, f);
  if (ferror(f) != 0)
    fprintf(stderr, "Failed to read file `%s`\n", filename);
  else
    buf[newlen++] = '\0';
  fclose(f);
  return buf;
}