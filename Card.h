// Project created by Nick Azcarate, Colby Lathrop, Gregory DeCanio, Asher Johnson Hogan, Davis Washburn, Spencer Warren on 4/14/18.

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
