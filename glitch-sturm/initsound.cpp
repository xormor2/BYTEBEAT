#include <Arduino.h>
#include <avr/io.h>
#include "def.hpp"

extern int SAMPLE_RATE;

void initSound()
{
    pinMode(speakerPin, OUTPUT);

    /*
    Clear bits EXCLK and AS2 from ASSR (Asynchronous Status Register)

    Bit 6 – EXCLK: Enable External Clock Input
    When EXCLK is written to one, and asynchronous clock is selected, the external clock input buffer is enabled and an external clock
    can be input on Timer Oscillator 1 (TOSC1) pin instead of a 32kHz crystal.

    Bit 5 – AS2: Asynchronous Timer/Counter2
    When AS2 is written to zero, Timer/Counter2 is clocked from the I/O clock, clkI/O. When AS2 is written to one, Timer/Counter2 is clocked from a crystal Oscillator connected to the Timer Oscillator pin.
    */
    ASSR &= ~(_BV(EXCLK) | _BV(AS2));

    /*
    TCCR2A – Timer/Counter Control Register A
    */
    TCCR2A |= _BV(WGM21) | _BV(WGM20);
    TCCR2B &= ~_BV(WGM22);

    // Do non-inverting PWM on pin OC2A (p.155)
    // On the Arduino this is pin 11.
    TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
    TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
    // No prescaler (p.158)
    TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set initial pulse width to the first sample.
    OCR2A = 0;

    // Set up Timer 1 to send a sample every interrupt.
    cli();

    // Set CTC mode (Clear Timer on Compare Match) (p.133)
    // Have to set OCR1A *after*, otherwise it gets reset to 0!
    TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
    TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));

    // No prescaler (p.134)
    TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set the compare register (OCR1A).
    // OCR1A is a 16-bit register, so we have to do this with
    // interrupts disabled to be safe.
    OCR1A = F_CPU / SAMPLE_RATE; // 16e6 / 8000 = 2000
    // Enable interrupt when TCNT1 == OCR1A (p.136)
    TIMSK1 |= _BV(OCIE1A);

    sei();
}
