/*
CC By Sa jeesus-bock & xormor2 2024
gcc sin.c -lm -o sin
*/
#include <stdio.h>
#include <math.h>
#include <unistd.h>

float mogrify(float t)
{
    double tmp = sin(t);
    return fabs(tmp) * 20;
}
int main(float t)
{
    float mod = 1;
    float modDelta = .01;
    for (;; t += .001)
    {

        mod += modDelta;
        if (mod > 1.5)
        {
            modDelta = -.002;
        }
        if (mod < 0.5)
        {
            modDelta = .002;
        }
        float val = mogrify(t);
        if (val * mod > 50)
        {
            val /= mod;
        }
        else
        {
            val *= mod;
        };

        putchar((char)val);
        usleep(10);
        // printf("%d \n", (char)val);
    }
    return 0;
}