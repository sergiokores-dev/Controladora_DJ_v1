#include <Arduino.h>
#include "shift.h"
#include "config.h"
#include "shift.h"
#include "jog.h"
#include "led_manager.h"

void setup()
{
    Serial.begin(115200);

    // SHIFT
    pinMode(SHIFT_PIN, INPUT_PULLUP);

    // JOG
    pinMode(ENCODER_S1, INPUT_PULLUP);
    pinMode(ENCODER_S2, INPUT_PULLUP);

    // LEDS
    initLeds();

    delay(500);

    Serial.println();
    Serial.println("========================");
    Serial.println("DJ CONTROLLER READY");
    Serial.println("========================");

    bootAnimation();
}

void loop()
{
    updateShift();

    updateJog();

    updateLeds(
        isShiftPressed()
    );
}