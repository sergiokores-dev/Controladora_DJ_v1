#include <Arduino.h>

#include "config.h"
#include "shift.h"

void updateJog()
{
    static String encoderSequence = "";

    int s1 = digitalRead(ENCODER_S1);
    int s2 = digitalRead(ENCODER_S2);

    String currentState =
        String(s1) + String(s2);

    static String lastState = currentState;

    if (currentState != lastState)
    {
        encoderSequence += currentState;

        // RIGHT
        if (encoderSequence.endsWith("1110000111"))
        {
            if (isShiftPressed())
            {
                Serial.println("BROWSER DOWN");
            }
            else
            {
                Serial.println("JOG RIGHT");
            }

            encoderSequence = "";
        }

        // LEFT
        if (encoderSequence.endsWith("1101001011"))
        {
            if (isShiftPressed())
            {
                Serial.println("BROWSER UP");
            }
            else
            {
                Serial.println("JOG LEFT");
            }

            encoderSequence = "";
        }

        if (encoderSequence.length() > 20)
        {
            encoderSequence = "";
        }

        lastState = currentState;
    }
}