#include <Arduino.h>

#include "config.h"
#include "deck_state.h"
#include "shift.h"
#include "jog.h"
#include "led_manager.h"

void setup()
{
    Serial.begin(115200);

    pinMode(SHIFT_PIN, INPUT_PULLUP);

    pinMode(
        ENCODER_S1,
        INPUT_PULLUP
    );

    pinMode(
        ENCODER_S2,
        INPUT_PULLUP
    );

    initLeds();

    delay(500);

    Serial.println();
    Serial.println("========================");
    Serial.println("DJ CONTROLLER READY");
    Serial.println("========================");

    Serial.println("CURRENT DECK -> A");

    bootAnimation();
}

void loop()
{
    updateShift();

    updateJog();
}