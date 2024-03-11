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
      if(!strcmp("playtune1",argv[1]))
      {
        for(;;t++)putchar(((t<<1)^((t<<3)+(t>>10)&t>>12))|t>>(4-(1^7&(t>>18)))|t>>7);
      }
		else if(!strcmp("playtune2",argv[1]))
		{
			for(;;t++)putchar(((t<<2)^((t<<1)+(t>>7)&t>>12))|t>>(4-(1^7&(t>>19)))|t>>7);
		}
		else if(!strcmp("playtune3",argv[1]))
		{
			for(;;t++)putchar(((t<<3)^((t<<1)+(t>>7)&t>>12))|t>>(4-(1^7&(t>>19)))|t>>7);
		}
		else if(!strcmp("playtune4",argv[1]))
		{
			for(;;t++)putchar(((t<<3)^((t<<4)+(t>>5)&t>>12))|t>>(4-(1^7&(t>>19)))|t>>7);
		}
		if(!strcmp("playtune5",argv[1]))
		{
			for(;;t++)putchar(((t<<3)^((t<<4)+(t>>5)&t>>12))|t>>(4-(1^7&(t>>23)))|t>>7);
		}
      else
      {
        puts("bad commandline argument!");
        return 1;
      }
  }
  return 0;
}