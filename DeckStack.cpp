/*
 * DeckStack.cpp
 *
 * by Nicolas Azcarate, Gregory DeCanio, Asher Johnson Hogan,
 * Colby Lathrop, Spencer Warren, and Davis Washburn
 */

#include "DeckStack.h"
using namespace std;

int myRandom2 (int i){
    return rand()%i;
}

void DeckStack::createDeck(){
    cardStack.push_back(new Card("A", "Hearts"));
    for(int i = 2; i <= 10; i++){
        cardStack.push_back(new Card(to_string(i), "Hearts"));
    }
    cardStack.push_back(new Card("J", "Hearts"));
    cardStack.push_back(new Card("Q", "Hearts"));
    cardStack.push_back(new Card("K", "Hearts"));

    cardStack.push_back(new Card("A", "Spades"));
    for(int i = 2; i <= 10; i++){
        cardStack.push_back(new Card(to_string(i), "Spades"));
    }
    cardStack.push_back(new Card("J", "Spades"));
    cardStack.push_back(new Card("Q", "Spades"));
    cardStack.push_back(new Card("K", "Spades"));

    cardStack.push_back(new Card("A", "Diamonds"));
    for(int i = 2; i <= 10; i++){
        cardStack.push_back(new Card(to_string(i), "Diamonds"));
    }
    cardStack.push_back(new Card("J", "Diamonds"));
    cardStack.push_back(new Card("Q", "Diamonds"));
    cardStack.push_back(new Card("K", "Diamonds"));

    cardStack.push_back(new Card("A", "Clubs"));
    for(int i = 2; i <= 10; i++){
        cardStack.push_back(new Card(to_string(i), "Clubs"));
    }
    cardStack.push_back(new Card("J", "Clubs"));
    cardStack.push_back(new Card("Q", "Clubs"));
    cardStack.push_back(new Card("K", "Clubs"));
}

void DeckStack::createDemoDeck() {
    cardStack.push_back(new Card("A", "Hearts"));
    cardStack.push_back(new Card("J", "Hearts"));
    cardStack.push_back(new Card("A", "Spades"));
    cardStack.push_back(new Card("J", "Spades"));
    for(int i = 2; i <= 10; i++){
        cardStack.push_back(new Card(to_string(i), "Hearts"));
    }
    cardStack.push_back(new Card("Q", "Hearts"));
    cardStack.push_back(new Card("K", "Hearts"));
    for(int i = 2; i <= 10; i++){
        cardStack.push_back(new Card(to_string(i), "Spades"));
    }
    cardStack.push_back(new Card("Q", "Spades"));
    cardStack.push_back(new Card("K", "Spades"));
    for(int i = 2; i <= 5; i++){
        cardStack.push_back(new Card(to_string(i), "Diamonds"));
    }
    cardStack.push_back(new Card("Q", "Diamonds"));
    cardStack.push_back(new Card("A", "Diamonds"));
    cardStack.push_back(new Card("A", "Clubs"));
    cardStack.push_back(new Card("K", "Diamonds"));
    for(int i = 8; i <= 10; i++){
        cardStack.push_back(new Card(to_string(i), "Diamonds"));
    }
    cardStack.push_back(new Card("J", "Diamonds"));
    for(int i = 2; i <= 10; i++){
        cardStack.push_back(new Card(to_string(i), "Clubs"));
    }
    cardStack.push_back(new Card("J", "Clubs"));
    cardStack.push_back(new Card("Q", "Clubs"));
    cardStack.push_back(new Card("K", "Clubs"));
}

DeckStack::DeckStack(int numDecks) {
    numberDecks = numDecks;
    if(numDecks == 7){
        for(int i = 0; i < 6; i++){
            createDemoDeck();
        }
    }else{
        for(int i = 0; i < numDecks; i++){
            createDeck();
        }
        shuffleDeck();
    }
}


void DeckStack::shuffleDeck() {
    random_shuffle(cardStack.begin(), cardStack.end(), myRandom2);
}

vector<Card *> DeckStack::getCardStack(){
    return this->cardStack;
}

Card * DeckStack::getTopCard(){
    return cardStack[0];
}

int DeckStack::getNumDecks() {
    return numberDecks;
}

Card * DeckStack::removeTopCard(){
    Card * temp = getTopCard();
    cardStack.erase(cardStack.begin());
    return temp;
}

void DeckStack::addCard(Card * card) {
    cardStack.push_back(card);
}
