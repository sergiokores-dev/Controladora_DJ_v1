#include <Arduino.h>
#include <FastLED.h>

#include "config.h"
#include "deck_state.h"

CRGB leds[NUM_LEDS];

void setDeckColor();

void initLeds()
{
    FastLED.addLeds<
        WS2811,
        LED_PIN,
        BRG
    >(
        leds,
        NUM_LEDS
    );

    FastLED.setBrightness(80);
}

void bootAnimation()
{
    CRGB colors[] =
    {
        CRGB::Blue,
        CRGB::Purple,
        CRGB::Red,
        CRGB::Green,
        CRGB::White
    };

    for (int c = 0; c < 5; c++)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = colors[c];
        }

        FastLED.show();

        delay(180);
    }

    setDeckColor();
}

void setDeckColor()
{
    CRGB deckColor;

    if (currentDeck == DECK_A)
    {
        deckColor = CRGB::Blue;
    }
    else
    {
        deckColor = CRGB::Red;
    }

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = deckColor;
    }

    FastLED.show();
}

void updateLeds(bool shiftPressed)
{
    static unsigned long lastUpdate = 0;
    static int brightness = 20;
    static int fadeDirection = 1;
    static bool lastShiftState = false;

    // SHIFT PRESSIONADO
    if (shiftPressed)
    {
        if (millis() - lastUpdate > 20)
        {
            lastUpdate = millis();

            brightness += fadeDirection * 3;

            if (brightness >= 120)
            {
                brightness = 120;
                fadeDirection = -1;
            }

            if (brightness <= 20)
            {
                brightness = 20;
                fadeDirection = 1;
            }

            for (int i = 0; i < NUM_LEDS; i++)
            {
                leds[i] = CRGB(
                    brightness,
                    brightness,
                    brightness
                );
            }

            FastLED.show();
        }
    }

    // SHIFT SOLTO
    else
    {
        // acabou de soltar
        if (lastShiftState)
        {
            setDeckColor();
        }
    }

    // salva estado anterior
    lastShiftState = shiftPressed;
}
