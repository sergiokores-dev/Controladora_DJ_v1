#include <Arduino.h>

#include "config.h"
#include "deck_state.h"

bool buttonPressed = false;
bool holdTriggered = false;
bool longHoldTriggered = false;

unsigned long pressStartTime = 0;
unsigned long lastDebounceTime = 0;

int lastButtonState = HIGH;
int currentButtonState = HIGH;

void updateShift()
{
    int reading = digitalRead(SHIFT_PIN);

    if (reading != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) >
        DEBOUNCE_TIME)
    {
        if (reading != currentButtonState)
        {
            currentButtonState = reading;

            if (currentButtonState == LOW)
            {
                buttonPressed = true;

                holdTriggered = false;
                longHoldTriggered = false;

                pressStartTime = millis();

                Serial.println("SHIFT PRESSED");
            }
            else
            {
                unsigned long pressDuration =
                    millis() - pressStartTime;

                if (pressDuration < HOLD_TIME)
                {
                    Serial.println("SHIFT TAP");
                }

                Serial.println("SHIFT RELEASED");

                buttonPressed = false;
            }
        }
    }

    if (buttonPressed &&
        !holdTriggered &&
        (millis() - pressStartTime >= HOLD_TIME))
    {
        holdTriggered = true;

        Serial.println("SHIFT HOLD");
    }

    if (buttonPressed &&
        !longHoldTriggered &&
        (millis() - pressStartTime >= LONG_HOLD_TIME))
    {
        longHoldTriggered = true;

        toggleDeck();

        if (currentDeck == DECK_A)
        {
            Serial.println("DECK MODE -> A");
        }
        else
        {
            Serial.println("DECK MODE -> B");
        }
    }

    lastButtonState = reading;
}

bool isShiftPressed()
{
    return buttonPressed;
}