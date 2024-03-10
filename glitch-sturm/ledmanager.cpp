#include <Arduino.h>
#include <avr/io.h>
#include "def.hpp"

extern bool isClockOutMode;
extern byte clocksOut, programNumber;
void ledManager()
{
    int val;
    if (isClockOutMode)
    {
        // show clocks
        clocksOut++;
        if (clocksOut == 16)
        {
            clocksOut = 0;
        }
        val = clocksOut;
    }
    else
    {
        // show program number in binary
        val = programNumber;
    }
    digitalWrite(ledBit0Pin, bitRead(val, 0));
    digitalWrite(ledBit1Pin, bitRead(val, 1));
    digitalWrite(ledBit2Pin, bitRead(val, 2));
    digitalWrite(ledBit3Pin, bitRead(val, 3));
}