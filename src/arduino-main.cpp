/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// the setup routine runs once when you press reset:
void setup() {
    // initialize the digital pin as an output.
    pinMode(16, OUTPUT);

    delay(1000);
    digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)

}

// the loop routine runs over and over again forever:
void loop() {
    // digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
    // delay(1000);
    // digitalWrite(16, LOW);    // turn the LED off by making the voltage LOW
    // delay(1000);
}