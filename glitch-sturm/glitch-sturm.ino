// Based on Glitch Storm 0.99 code
// CC By Sa Spherical Sound Society 2020
// Heavy inspiration in Bytebeat (Viznut)
// Some equations are empty. You can collaborate sending your new finding cool sounding ones to the repository
// https://github.com/spherical-sound-society/glitch-storm
//
// CC By Sa jeesus-bock & xormor2 2024

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <HardwareSerial.h>

#include "def.hpp"
#include "initsound.hpp"
#include "controlmanagers.hpp"
#include "ledmanager.hpp"

// int SAMPLE_RATE = 4096;
// int SAMPLE_RATE = 8192;
// int SAMPLE_RATE = 9216;
// int SAMPLE_RATE = 22000;

int debounceRange = 20; // 5
long t = 0;
volatile int a, b, c;
volatile int value;
byte programNumber = 1;
byte rightButtonState = 0;
byte leftButtonState = 0;
byte lastButtonState = 0;
byte totalPrograms = 16;
byte clocksOut = 0;
int cyclebyte = 0;
volatile int aTop = 99;
volatile int aBottom = 0;
volatile int bTop = 99;
volatile int bBottom = 0;
volatile int cTop = 99;
volatile int cBottom = 0;
int d = 0;
bool isClockOutMode = false;
bool isSerialValues = true;
unsigned long time_now = 0;

long rightButtonTimer = 0;
long longPressRightTime = 400;
long leftButtonTimer = 0;
long longPressLeftTime = 400;
boolean isRightButtonActive = false;
boolean isLongPressRightActive = false;
boolean isLeftButtonActive = false;
boolean isLongPressLeftActive = false;

int shift_A_Pot = 1;
int old_A_Pot = 1;
int SAMPLE_RATE = 16384;
int old_SAMPLE_RATE = SAMPLE_RATE;
byte shift_C_Pot = 0;
byte old_C_Pot = 0;

void setup()
{

  // ledPin isn't used at all, it's the builtin led.
  pinMode(ledPin, OUTPUT);

  // These are the glitch storm 3 leds.
  pinMode(progBit0Pin, OUTPUT);
  pinMode(progBit1Pin, OUTPUT);
  pinMode(progBit2Pin, OUTPUT);
  pinMode(progBit3Pin, OUTPUT);

  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(leftButtonPin, INPUT_PULLUP);

  initSound();
  ledManager();

  if (isDebugging)
  {
    Serial.begin(9600);
  }
}

void loop()
{

  buttonsManager();
  potsManager();

  // slow loop show serial once every second
  if (isDebugging)
  {
    if (millis() > time_now + 1000)
    {
      time_now = millis();
      printValues();
    }
  }

  // long putin=analogRead(3);
  // int d = map(analogRead(3), 0, 1023, 0, 1023);
  //  timestrech(d);

  // Serial.println(analogRead(3));
  // c = (cBottom + cTop) >> 1;
  //  SAMPLE_RATE = map(analogRead(3), 0, 1023, 256, 32768);

  // this only if sample rate is different.
  // OCR1A = F_CPU / SAMPLE_RATE;
}

void printValues()
{
  Serial.print("programNumber: ");
  Serial.println(programNumber);
  Serial.print("A: ");
  Serial.print(a);
  Serial.print(" B: ");
  Serial.print(b);
  Serial.print(" C: ");
  Serial.println(c);
}

ISR(TIMER1_COMPA_vect)
{
  /*
  t is the increasing value of timer.
  a, b, c are pins 0,1,2 values read and mapped to limits set by aTop and aBottom values
  these pins are connected to the potentiometers. TODO: figure out which pin for which knob.
  */
  switch (programNumber)
  {
  case 1:
    value = ((t & ((t >> a))) + (t | ((t >> b)))) & (t >> (c + 1)) | (t >> a) & (t * (t >> b));

    aTop = 10;
    aBottom = 0;
    bTop = 14;
    bBottom = 0;
    cTop = 14;
    cBottom = 0;
    break;
  case 2:

    if (t > 65536)
      t = -65536;
    value = (t >> c | a | t >> (t >> 16)) * b + ((t >> (b + 1)) & (a + 1));
    aTop = 12;
    aBottom = 0;
    bTop = 20;
    bBottom = 4;
    cTop = 12;
    cBottom = 5;
    break;
  case 3:
    // value = t>>6^t&37|t+(t^t>>11)-t*((t%a?2:6)&t>>11)^t<<1&(t&b?t>>4:t>>10);
    value = t >> c ^ t & 37 | t + (t ^ t >> a) - t * ((t >> a ? 2 : 6) & t >> b) ^ t << 1 & (t & b ? t >> 4 : t >> 10);
    aTop = 30;
    aBottom = 6;
    bTop = 16;
    bBottom = 0;
    cTop = 10;
    cBottom = 0;

    break;
  case 4:
    // value = t>>6^t&37|t+(t^t>>11)-t*((t%a?2:6)&t>>11)^t<<1&(t&b?t>>4:t>>10);
    value = b * t >> a ^ t & (37 - c) | t + ((t ^ t >> 11)) - t * ((t >> 6 ? 2 : a) & t >> (c + b)) ^ t << 1 & (t & 6 ? t >> 4 : t >> c);
    aTop = 12;
    aBottom = 0;
    bTop = 16;
    bBottom = 0;
    cTop = 10;
    cBottom = 0;
    break;
  case 5:
    // t>>6^t&37|t+(t^t>>11)-t*((t%a?2:6)&t>>11)^t<<1&(t&b?t>>4:t>>10);
    // value = t+(t&t^t>>6)-t*((t>>9)&(t%16?2:6)&t>>9)
    // value = t+(t&t^t>>(b*2-c))-t*((t>>a)&(t%c?2:(a-c))&t>>b);
    value = c * t >> 2 ^ t & (30 - b) | t + ((t ^ t >> b)) - t * ((t >> 6 ? a : c) & t >> (a)) ^ t << 1 & (t & b ? t >> 4 : t >> c);
    aTop = 24;
    aBottom = 0;
    bTop = 22;
    bBottom = 0;
    cTop = 16;
    cBottom = 0;
    break;
  case 6:
    // value = ((t>>a&t)-(t>>a)+(t>>a&t))+(t*((t>>b)&b));
    value = ((t >> a & t) - (t >> a) + (t >> a & t)) + (t * ((t >> c) & b));

    aTop = 10;
    aBottom = 3;
    bTop = 28;
    bBottom = 0;
    cTop = 10;
    cBottom = 3;
    break;
  case 7:
    // SE CUELGA A 16KH
    //  value = ((t % 42 + b) * (a >> t) | (128 & b) - (t >> a)) % (t >> b) ^ (t & (t >> c));
    // value =  t>>b&t?t>>a:-t>>c ;
    value = t >> b & t ? t >> a : -t >> c;

    aTop = 10;
    aBottom = 0;
    bTop = 22;
    bBottom = 10;
    cTop = 8;
    cBottom = 0;
    break;
  case 8:
    // 16kh only work by 65536 loops
    if (t > 65536)
      t = -65536;
    value = (t >> a | c | t >> (t >> 16)) * b + ((t >> (b + 1)));
    aTop = 12;
    aBottom = 0;
    bTop = 20;
    bBottom = 0;
    cTop = 20;
    cBottom = 0;
    break;
  case 9:
    // value = ((t*(t>>a|t>>(a+1))&b&t>>8))^(t&t>>13|t>>6);
    value = ((t * (t >> a | t >> (a & c)) & b & t >> 8)) ^ (t & t >> c | t >> 6);
    aTop = 16;
    aBottom = 0;
    bTop = 86;
    bBottom = 0;
    cTop = 26;
    cBottom = 0;
    break;
  case 10:
    // value = ((t>>32)*7|(t>>a)*8|(t>>b)*7)&(t>>7);
    value = ((t >> c) * 7 | (t >> a) * 8 | (t >> b) * 7) & (t >> 7);
    aTop = 8;
    aBottom = 0;
    bTop = 22;
    bBottom = 0;
    cTop = 13;
    cBottom = 0;
    break;
  case 11:
    // % is a too heavy operatin for atmel 328. Should not be used in any equation. Change it
    // value = ((t >> a % (128-b<<t))) * b * t >>( c*t<<4) * t >> 18 ;
    // DEFFO
    value = ((t >> a % (128 - b << (t >> (9 - c))))) * b * t >> (c * t << 4) * t >> 18;
    //
    // value = ((t >> a % (128-b<<(t>>(9-c))))) * b * t >>( c*t<<4) * t >> 18+(t >> c ? 2 : a)&t * (t >> b) ;

    // value = ((t >> 6 ? 2 : a)&t * (t >> c) | ( b) - (t >> a)) % (t >> b) + (4 | (t >> c));
    // value = ((t >> b ? c : a)&t * (a) | ( 8) - (t >> 1)) % (t >> b) + (4 | (t >> c));
    aTop = 16;
    aBottom = 4;
    bTop = 22;
    bBottom = 1;
    cTop = 9;
    cBottom = 2;
    break;
  case 12:
    // moola long
    value = (t * 12 & t >> a | t * b & t >> c | t * b & c / (b << 2)) - 2;
    // value = (t * a & t >> b | t * c & t >> 7 | t * 3 & t / 1024) - 1;
    aTop = 18;
    aBottom = 0;
    bTop = 8;
    bBottom = 1;
    cTop = 14;
    cBottom = 5;
    break;
  case 13:
    // moola viznu
    // value = (t * 5 & t >> 7) | (t * 3 & t >> 10);
    value = ((t * (t >> a) & (b * t >> 7) & (8 * t >> c)));
    aTop = 18;
    aBottom = 10;
    bTop = 14;
    bBottom = 1;
    cTop = 10;
    cBottom = 1;
    break;

  case 14:
    // Both cool. What to choose?
    // value=t>>c^t&1|t+(t^t>>21)-t*((t>>4?b:a)&t>>12)^t<<1&(a&12?t>>4:t>>10);
    value = t >> c ^ t & 1 | t + (t ^ t >> 21) - t * ((t >> 4 ? b : a) & t >> (12 - (a >> 1))) ^ t << 1 & (a & 12 ? t >> 4 : t >> 10);
    aTop = 8;
    aBottom = 0;
    bTop = 16;
    bBottom = 0;
    cTop = 1;
    cBottom = 6;
    break;
  case 15:

    // value = (t*((t>>a|t<<c)&29&t>>b));
    //((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t))
    // value=((t&(a<<a))?((t*(t^t%b)|(t>>c))>>1):(t>>3)|((t&(b<<b))?t<<2:t));
    //  value = ((t & (4 << c)) ? ((t * (t ^ t & a) | (t >> b)) >> 1) : (t >> 4) | ((t & (c << b)) ? t << 1 : t));
    // value = ((t &  (4 << a)) ? ((-t * (t ^ t ) | (t >> b)) >> c) : (t >> 4) | ((t & (c << b)) ? t << 1 : t));
    value = ((t & (4 << a)) ? ((-t * (t ^ t) | (t >> b)) >> c) : (t >> 4) | ((t & (c << b)) ? t << 1 : t));
    aTop = 8;
    aBottom = 0;
    bTop = 9;
    bBottom = 0;
    cTop = 5;
    cBottom = 0;
    break;
  case 16:
    value = ((t & (4 << a)) ? ((-t * (t ^ t) | (t >> b)) >> 3) : (t >> c) | ((t & (3 << b)) ? t << 1 : t));
    aTop = 8;
    aBottom = 0;
    bTop = 9;
    bBottom = 0;
    cTop = 6;
    cBottom = 0;
    break;
  }

  OCR2A = value;
  t += shift_A_Pot;

  // timing  clockout easter-egg mode
  cyclebyte++;
  if (cyclebyte == 1024)
  {
    cyclebyte = 0;
    if (isClockOutMode)
    {
      ledManager();
    }
  }
}
