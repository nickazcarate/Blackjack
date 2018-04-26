/*
 * DeckStack.h
 *
 * by Nicolas Azcarate, Gregory DeCanio, Asher Johnson Hogan,
 * Colby Lathrop, Spencer Warren, and Davis Washburn
 */

#ifndef BLACKJACK_DECKSTACK_H
#define BLACKJACK_DECKSTACK_H

#include "Card.h"

#include <cstring>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//Initialize the DeckStack Object
class DeckStack {
private:

    void createDeck();
    void createDemoDeck();
    vector<Card *> cardStack;
    int numberDecks;

public:

    DeckStack(int numDecks);
    void shuffleDeck();
    vector<Card *> getCardStack();
    Card * getTopCard();
    int getNumDecks();

    // removes and returns to avoid having to call both functions
    Card * removeTopCard();
    void addCard(Card *);

};


#endif //BLACKJACK_DECKSTACK_H
