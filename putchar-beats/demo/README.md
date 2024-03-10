# Demo

A little demo of the sound generated

- Compile the programn `gcc mu5.c -o mu5` (the .c file is in the parent dir along with the others.)
- Run the program, piping output to file `./mu5 > tune.pcm` Be quick, the tune is generated at
super-speed and you'll end up with a huge file if you're not careful.
- Convert the PCM data to WAV `ffmpeg -f s8 -ar 8000 -ac 1 -i tune.pcm tune.wav`

(tune.pcm file removed from version control as it was 21 megs large.)
