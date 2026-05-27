#pragma once

enum DeckMode
{
    DECK_A,
    DECK_B
};

extern DeckMode currentDeck;

void toggleDeck();