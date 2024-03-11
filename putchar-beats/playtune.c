#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
  int t;
  if (argc==1)
  {
    for(;;t++)putchar(((t<<1)^((t<<3)+(t>>10)&t>>12))|t>>(4-(1^7&(t>>18)))|t>>7);
  }
  else if (argc>1)
  {
      if(!strcmp("playtune",argv[1]))
      {
        for(;;t++)putchar(((t<<1)^((t<<3)+(t>>10)&t>>12))|t>>(4-(1^7&(t>>18)))|t>>7);
      }
      else
      {
        puts("bad commandline argument!");
        return 1;
      }
  }
  return 0;
}