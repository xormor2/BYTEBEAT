#include <stdio.h>
main(t){for(;;t++)putchar(((t<<1)^((t<<3)+(t>>10)&t>>12))|t>>(4-(1^7&(t>>18)))|t>>7);}
