#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TUNE1 ((t << 1) ^ ((t << 3) + (t >> 10) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 18))) | t >> 7
#define TUNE2 ((t << 1) ^ ((t << 3) + (t >> 10) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 18))) | t >> 7
#define TUNE3 ((t << 2) ^ ((t << 1) + (t >> 7) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7
#define TUNE4 ((t << 3) ^ ((t << 1) + (t >> 7) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7
#define TUNE5 ((t << a) ^ ((t << 4) + (t >> 5) & t >> b)) | t >> (4 - (1 ^ 7 & (t >> c))) | t >> 7
#define TUNE6 ((t << 3) ^ ((t << 4) + (t >> 5) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 23))) | t >> 7
int main(int argc, char *argv[])
{
  int t;
  int a, b, c, aDelta, bDelta, cDelta = 1;
  long outputbytes = 0;
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
      a = 3;
      b = 3;
      c = 3;
      aDelta = 1;
      bDelta = 10;
      cDelta = 10;
      for (;; t++)
      {
        if (t % 1000 == 0)
          a += aDelta;
        if (a == 4)
          aDelta = -1;
        if (a == 1)
          aDelta = 1;

        if (t % 2000 == 0)
          b++;
        if (b == 18)
          bDelta = -1;
        if (b == 10)
          bDelta = 1;

        if (t % 3000 == 0)
          c++;
        if (c == 18)
          cDelta = -1;
        if (c == 10)
          cDelta = 1;

        outputbytes++;
        if (outputbytes == 100000)
          exit(1);
        putchar(TUNE5);
      }
    }
    if (!strcmp("5", argv[1]))
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