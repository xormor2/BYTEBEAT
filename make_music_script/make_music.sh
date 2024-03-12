# a script to make music copyleft 2024 xormor2
# the script is made chmod +x make_music.sh -v
# and run with ./make_music.sh musicfile_without_file_extension
# for example "./make_music.sh test" makes test.pcm into test.wav
# and test.wav into test.mp3
ffmpeg -f s8 -ar 8000 -ac 1 -i $*.pcm $*.wav
ffmpeg -i $*.wav -codec:a libmp3lame -qscale:a 2 $*.mp3
