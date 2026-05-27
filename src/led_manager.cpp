#include <Arduino.h>
#include <FastLED.h>

#include "config.h"
#include "deck_state.h"

//void setDeckColor();

CRGB leds[NUM_LEDS];

// =====================
// JOG ANIMATION
// =====================

int jogPosition = 0;
 
int ledMap[11] =
{
    0,1,2,3,4,5,10,9,8,7,6
};


void setDeckColor()
{
    CRGB deckColor;

    if (currentDeck == DECK_A)
    {
        deckColor = CRGB::Green;
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

        delay(100);
    }

    setDeckColor();
}



void moveJogPosition(int direction)
{
    jogPosition += direction;

    if (jogPosition >= NUM_LEDS)
    {
        jogPosition = 0;
    }

    if (jogPosition < 0)
    {
        jogPosition = NUM_LEDS - 1;
    }
}


void updateLeds(bool shiftPressed)
{
    static unsigned long lastUpdate = 0;
    static int brightness = 20;
    static int fadeDirection = 1;
    static bool lastShiftState = false;

    // =========================
    // SHIFT MODE
    // =========================

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

    // =========================
    // NORMAL MODE
    // =========================

    else
    {
        // acabou de soltar SHIFT
        if (lastShiftState)
        {
            setDeckColor();
        }

        // cor base do deck
        setDeckColor();

        // marcador do jog
        leds[
            ledMap[jogPosition]
        ] = CRGB::White;

        FastLED.show();
    }

    lastShiftState = shiftPressed;
}