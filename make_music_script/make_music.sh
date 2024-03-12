# make_music.sh: a script to make music, copyleft 2024 xormor2
#
# The script is made chmod +x make_music.sh -v
# and run with ./make_music.sh musicfile_without_file_extension.
# For example "./make_music.sh test" makes test.pcm into test.wav
# and test.wav into test.mp3.
#
# The original file is made with gcc -o musicfile musicfile.c
# and ./musicfile > musicfile.pcm (press Ctrl+C after a few seconds,
# because the file will become big after a few seconds).
# then run ./make_music.sh musicfile WITHOUT the extension (*.pcm)
ffmpeg -f s8 -ar 8000 -ac 1 -i $*.pcm $*.wav
ffmpeg -i $*.wav -codec:a libmp3lame -qscale:a 2 $*.mp3
