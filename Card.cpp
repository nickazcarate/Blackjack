// Created by Nick Azcarate on 4/14/18.

#include "Card.h"

//Anotha one

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