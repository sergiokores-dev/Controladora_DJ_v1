#include "deck_state.h"
#include "led_manager.h"

DeckMode currentDeck = DECK_A;

void toggleDeck()
{
    if (currentDeck == DECK_A)
    {
        currentDeck = DECK_B;
    }
    else
    {
        currentDeck = DECK_A;
    }

    setDeckColor();
}