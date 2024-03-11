# putchar-beats

### Linux

You probably already have them, but if the gcc command doesn't work, install gcc and libc-dev packages with your choice of package manager.

Compile the .c files with gcc or clang (no dependencies besides libc) and run with `./binaryfile > /dev/dsp` (tested on Debian bookworm 12 stable).

`playtune.c` takes a number 1-5 as a command line argument to choose the algo.

### Windows

I honestly don't have a clue. Googling for "bytebeats windows" gives a whole bunch of results so maybe not all hope is lost, meanwhile check the demo.

Check out the demo directory for a WAV demo of a tune.

### Technical babbling

"/dev/dsp expects 8-bit unsigned mono audio at a sample rate of 8000 Hz." That's a good starting point. Some modulation could be achieved by playing the PCM signal at varying speed.
