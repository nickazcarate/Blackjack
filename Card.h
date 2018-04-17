// Created by Nick Azcarate on 4/14/18.

#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H

using namespace std;
#include <cstring>
#include <string>

class Card {
public:
    Card(string value, string suit);
    string getValue();
    string getSuit();
    string print();
private:
    string value;
    string suit;
};


#endif //BLACKJACK_CARD_H
