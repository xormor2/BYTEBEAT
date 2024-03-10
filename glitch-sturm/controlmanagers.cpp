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
extern bool isRightButtonActive;
extern bool isLeftButtonActive;
extern bool isLongPressLeftActive;
extern bool isLongPressRightActive, isClockOutMode;
extern int oldLeftPot;
extern int shiftLeftPot;
extern int old_SAMPLE_RATE;
extern int SAMPLE_RATE;
extern int a, b, c, debounceRange;
extern long rightButtonTimer, longPressRightTime, leftButtonTimer, longPressLeftTime;
extern byte programNumber, rightButtonState, leftButtonState, lastButtonState, totalPrograms, clocksOut;

// Only change if the change is big enough.
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
    int actualLeftPot = map(analogRead(leftPotPin), 0, 1023, -7, 7);

    if (oldLeftPot != actualLeftPot)
    {

        shiftLeftPot = actualLeftPot;
    }
    oldLeftPot = actualLeftPot;

    if (shiftLeftPot == 0)
    {
        // prevents the engine to stop
        shiftLeftPot = 1;
    }
}
void leftLongPressActions()
{

    // SAMPLE RATE *************************************

    old_SAMPLE_RATE = SAMPLE_RATE;
    // int actual_SAMPLE_RATE = analogRead(1);
    SAMPLE_RATE = softDebounce(analogRead(leftPotPin), SAMPLE_RATE);

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
    if (digitalRead(rightButtonPin) == LOW)
    {
        if (isRightButtonActive == false)
        {
            isRightButtonActive = true;
            rightButtonTimer = millis();
            Serial.println("RIGHT button short press");
        }
        if ((millis() - rightButtonTimer > longPressRightTime) && (isLongPressRightActive == false))
        {
            isLongPressRightActive = true;

            Serial.println("RIGHT long press ON");
        }
    }
    else
    {
        if (isRightButtonActive == true)
        {
            if (isLongPressRightActive == true)
            {
                isLongPressRightActive = false;

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
            isRightButtonActive = false;
        }
    }
    // end RIGHT button
    // start LEFT button
    if (digitalRead(leftButtonPin) == LOW)
    {
        if (isRightButtonActive == false)
        {
            isRightButtonActive = true;
            leftButtonTimer = millis();
            Serial.println("LEFT button short press");
        }
        if ((millis() - leftButtonTimer > longPressLeftTime) && (isLongPressLeftActive == false))
        {
            isLongPressLeftActive = true;

            Serial.println("LEFT BUTTON long press ON");
        }
    }
    else
    {
        if (isLeftButtonActive == true)
        {
            if (isLongPressLeftActive == true)
            {
                isLongPressLeftActive = false;
                Serial.println("LEFT BUTTON long press release");
                pressBothButtons = true;
                // isClockOutMode = !isClockOutMode;
                // we only change program in short pressed, not long ones
                programNumber++;
            }
            else
            {
                if (leftButtonState == LOW)
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
                isLeftButtonActive = false;
            }
        }
        // end button 2

        // TODO Figure this out
        if (!isLongPressLeftActive && isLongPressRightActive && pressBothButtons)
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