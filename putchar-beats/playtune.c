#include <stdio.h>
#include <string.h>
#define TUNE1 ((t << 1) ^ ((t << 3) + (t >> 10) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 18))) | t >> 7
#define TUNE2 ((t << 1) ^ ((t << 3) + (t >> 10) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 18))) | t >> 7
#define TUNE3 ((t << 2) ^ ((t << 1) + (t >> 7) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7
#define TUNE4 ((t << 3) ^ ((t << 1) + (t >> 7) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7
#define TUNE5 ((t << 3) ^ ((t << 4) + (t >> 5) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7
#define TUNE6 ((t << 3) ^ ((t << 4) + (t >> 5) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 23))) | t >> 7
int main(int argc, char *argv[])
{
  int t;
  if (argc == 1)
  {
    for (;; t++)
      putchar(TUNE1);
  }
  else if (argc > 1)
  {
    if (!strcmp("1", argv[1]))
    {
      for (;; t++)
        putchar(TUNE2);
    }
    else if (!strcmp("2", argv[1]))
    {
      for (;; t++)
        putchar(TUNE3);
    }
    else if (!strcmp("3", argv[1]))
    {
      for (;; t++)
        putchar(TUNE4);
    }
    else if (!strcmp("4", argv[1]))
    {
      for (;; t++)
        putchar(TUNE5);
    }
    else if (!strcmp("5", argv[1]))
    {
      for (;; t++)
        putchar(TUNE6);
    }
    else
    {
      puts("bad commandline argument!");
      return 1;
    }
  }
  return 0;
}
