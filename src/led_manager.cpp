#include <Arduino.h>
#include <FastLED.h>
#include "deck_state.h"
#include "config.h"


void setDeckColor();

CRGB leds[NUM_LEDS];

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