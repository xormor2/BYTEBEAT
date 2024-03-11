/*
CC By Sa jeesus-bock % xormor2 2024
Credits to https://kiritchatterjee.wordpress.com/2014/11/10/a-simple-digital-low-pass-filter-in-c/
*/
#include <stdio.h>
float smoothData;
float LPF_Beta = 0.025; // 0<ß<1
main(t)
{
    for (;; t++)
    {
        int rawData = ((t << 1) ^ ((t << 1) + (t >> 7) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 2))) | t >> 7;
        smoothData = smoothData - (LPF_Beta * (smoothData - rawData));
        putchar(smoothData);
    }
}
