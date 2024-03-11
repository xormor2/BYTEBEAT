/*
CC By Sa jeesus-bock & xormor2 2024
gcc atan.c -lm -o atan
*/
#include <stdio.h>
#include <math.h>
char mogrify(int t)
{
    double tmp = atan(t) * 255;
    char *pointer = (char *)&tmp;
    char first = pointer[0];
    return first;
}
int main(int t)
{

    for (;; t++)
    {
        putchar(mogrify(t));
    }
    return 0;
}