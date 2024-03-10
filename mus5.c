#include <stdio.h>
main(t){for(;;t++)putchar(((t<<3)^((t<<4)+(t>>5)&t>>12))|t>>(4-(1^7&(t>>19)))|t>>7);}
