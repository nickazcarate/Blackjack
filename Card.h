/*
 * Card.h
 *
 * by Nicolas Azcarate, Gregory DeCanio, Asher Johnson Hogan,
 * Colby Lathrop, Spencer Warren, and Davis Washburn
 */

#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H

#include <cstring>
#include <string>
using namespace std;

//Initialize the Card Object
class Card {

private:

    string value;
    string suit;

public:

    Card(string value, string suit);
    string getValue();
    string getSuit();
    int getNumericValue();

};

#endif //BLACKJACK_CARD_H
