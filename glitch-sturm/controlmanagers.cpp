#include <Arduino.h>
#include <avr/io.h>
#include <HardwareSerial.h>

#include "ledmanager.hpp"
#include "def.hpp"

extern int aBottom;
extern int aTop;
extern int bBottom;
extern int bTop;
extern int cBottom;
extern int cTop;
extern bool isButton1Active;
extern bool isButton2Active;
extern bool isLongPress2Active;
extern bool isLongPress1Active, isClockOutMode;
extern int old_A_Pot;
extern int shift_A_Pot;
extern int old_SAMPLE_RATE;
extern int SAMPLE_RATE;
extern int a, b, c, debounceRange;
extern long button1Timer, longPress1Time, button2Timer, longPress2Time;
extern byte programNumber, upButtonState, downButtonState, lastButtonState, totalPrograms, clocksOut;

int softDebounce(int readCV, int oldRead)
{
    if (abs(readCV - oldRead) > debounceRange)
    {
        return readCV;
    }
    return oldRead;
}

void rightLongPressActions()
{

    // REVERSE TIME *********************
    int actual_A_Pot = map(analogRead(0), 0, 1023, -7, 7);

    if (old_A_Pot != actual_A_Pot)
    {

        shift_A_Pot = actual_A_Pot;
    }
    old_A_Pot = actual_A_Pot;

    if (shift_A_Pot == 0)
    {
        // prevents the engine to stop
        shift_A_Pot = 1;
    }
}
void leftLongPressActions()
{

    // SAMPLE RATE *************************************

    old_SAMPLE_RATE = SAMPLE_RATE;
    // int actual_SAMPLE_RATE = analogRead(1);
    SAMPLE_RATE = softDebounce(analogRead(0), SAMPLE_RATE);

    // actual_SAMPLE_RATE=map(analogRead(1), 0, 1023, 256, 16384);
    if (SAMPLE_RATE != old_SAMPLE_RATE)
    {
        // el mapeo se hace aqui
        // map(analogRead(1), 0, 1023, 256, 16384);
        int mappedSAMPLE_RATE = map(SAMPLE_RATE, 0, 1023, 256, 16384);
        OCR1A = F_CPU / mappedSAMPLE_RATE;
    }

    // TO BE PROGRAMMED ELASTIC STUFF ***********************
    // shift_C_Pot = map(analogRead(2), 0, 1023, 0, 15);
}

void buttonsManager()
{
    bool pressBothButtons = false;
    // start button 1
    if (digitalRead(upButtonPin) == LOW)
    {
        if (isButton1Active == false)
        {
            isButton1Active = true;
            button1Timer = millis();
            Serial.println("RIGHT button short press");
        }
        if ((millis() - button1Timer > longPress1Time) && (isLongPress1Active == false))
        {
            isLongPress1Active = true;

            Serial.println("RIGHT long press ON");
        }
    }
    else
    {
        if (isButton1Active == true)
        {
            if (isLongPress1Active == true)
            {
                isLongPress1Active = false;

                Serial.println("RIGHT long press RELEASE");
            }
            else
            {

                if (programNumber != totalPrograms)
                {
                    programNumber++;
                }
                else if (programNumber == totalPrograms)
                {
                    programNumber = 1;
                }
                Serial.println("RIGHT button short release");
                Serial.print("PROGRAM: ");
                Serial.println(programNumber);
                ledManager();
            }
            isButton1Active = false;
        }
    }
    // end RIGHT button
    // start LEFT button
    if (digitalRead(downButtonPin) == LOW)
    {
        if (isButton2Active == false)
        {
            isButton2Active = true;
            button2Timer = millis();
            Serial.println("LEFT button short press");
        }
        if ((millis() - button2Timer > longPress2Time) && (isLongPress2Active == false))
        {
            isLongPress2Active = true;

            Serial.println("LEFT BUTTON long press ON");
        }
    }
    else
    {
        if (isButton2Active == true)
        {
            if (isLongPress2Active == true)
            {
                isLongPress2Active = false;
                Serial.println("LEFT BUTTON long press release");
                pressBothButtons = true;
                // isClockOutMode = !isClockOutMode;
                // we only change program in short pressed, not long ones
                programNumber++;
            }
            else
            {
                if (downButtonState == LOW)
                {
                    if (programNumber > 1)
                    {
                        programNumber--;
                    }
                    else if (programNumber == 1)
                    {
                        programNumber = totalPrograms;
                    }
                    Serial.println("LEFT BUTTON short release");
                }
                ledManager();
                isButton2Active = false;
            }
        }
        // end button 2

        if (!isLongPress2Active && isLongPress1Active && pressBothButtons)
        {
            Serial.println("HACKKK");
            isClockOutMode = !isClockOutMode;
        }
    }
}

void potsManager()
{

    if (!isButton1Active && !isButton2Active)
    {
        // map(value, fromLow, fromHigh, toLow, toHigh)
        a = map(analogRead(0), 0, 1023, aBottom, aTop);
        b = map(analogRead(1), 0, 1023, bBottom, bTop);
        c = map(analogRead(2), 0, 1023, cBottom, cTop);
    }
    if (isLongPress2Active)
    {

        // left button is pressed
        leftLongPressActions();
    }
    if (isLongPress1Active)
    {

        // right button is pressed
        rightLongPressActions();
    }
}