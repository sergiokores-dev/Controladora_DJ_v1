#include <Arduino.h>
#include <FastLED.h>

#include "config.h"
#include "deck_state.h"

CRGB leds[NUM_LEDS];

void initLeds()
{
    FastLED.addLeds<WS2811, LED_PIN, RGB>(
        leds,
        NUM_LEDS
    );

    FastLED.setBrightness(80);
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

        delay(200);
    }

    setDeckColor();
}