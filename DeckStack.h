// Created by Nick Azcarate on 4/14/18.

#ifndef BLACKJACK_DECKSTACK_H
#define BLACKJACK_DECKSTACK_H
#include "Card.h"

using namespace std;
#include <cstring>
#include <string>
#include <iostream>
#include <vector>

class DeckStack {
private:
    void createDeck();
    vector<Card *> cardStack;
public:
    DeckStack(int numDecks);
    void printDeck();
    void shuffleDeck();
    vector<Card *> getCardStack();
    Card * getTopCard();
    Card * removeTopCard(); // removes and returns to avoid having to call both functions



};


#endif //BLACKJACK_DECKSTACK_H
