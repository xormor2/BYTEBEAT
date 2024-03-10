# Sound generation algorithms
The algorithms, or functions glitch-sturm supports are somewhat enhanced versions of traditional 
bytebeats where the only variable is ever increasing t integer.

### Example
```C
value = ((t * (t >> a) & (b * t >> 7) & (8 * t >> c)));
aTop = 18;
aBottom = 10;
bTop = 14;
bBottom = 1;
cTop = 10;
cBottom = 1;
```
### Variables
There are three variables: a,b and c that can be used in the function. Each one of these have a top and a bottom value
that ought to be set along defining the function. The top and bottom values make up a range how much the value can change.
The values are changed using knobs on the Glitch Storm board.

Instead of putcharring the calculation result value it's being put into a variable _value_ which is used then to generate the sound.
Technically value is the roof amount of voltage sent to pin 11, ie. the audio plug on board.

glitch-sturm has total of sixteen of these functions coded into it (It's possible more could be atted, there's no technical 
limitation that I know of for this.)
