/*
CC By Sa jeesus-bock & xormor2 2024
gcc sin.c -lm -o sin
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float mogrify(float t)
{
    return sin(t / 20) * 20 + 20;
}
int main(float t)
{
    float mod = 1;
    float modDelta = .02;
    for (;; t += (rand() % 100) / 100000.0)
    {

        mod += modDelta;
        if (mod > 1.5)
        {
            modDelta = -.02;
        }
        if (mod < 0.5)
        {
            modDelta = .02;
        }
        float val = mogrify(t);
        val *= mod;

        // printf("%d\n", (char)val);
        putchar(val);
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = rand() % 999;
        nanosleep(&ts, NULL);
    }
    return 0;
}