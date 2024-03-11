# Beats using maths

A bit more complicated code with the help of math.h functions.

Compile files with `-lm` switch, like: `gcc atan.c -lm -o atan`.

I tested using usleep for delaying the signal but with no results. A bit better luck with nanosleep,
but I don't think they offer much for this experiment.
