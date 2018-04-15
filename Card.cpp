// Created by Nick Azcarate on 4/14/18.

#include "Card.h"

Card::Card(string value, string suit){
    this->value = value;
    this->suit = suit;
}

//Nick's comment here!
string Card::getValue(){
    return this->value;
}
string Card::getSuit(){
    return this->suit;
}
// Greg's test comment