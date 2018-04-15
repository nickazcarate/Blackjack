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
public:
    DeckStack(int numDecks);
    void shuffleEntireDeck();
    void printDeck();
    void shuffleDeck();
    vector<Card *> getCardStack();
private:
    void createDeck();
    vector<Card *> cardStack;

};


#endif //BLACKJACK_DECKSTACK_H
