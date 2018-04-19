// Created by Nick Azcarate on 4/14/18.

#include "Card.h"


Card::Card(string value, string suit){
    //test comment HERE
    this->value = value;
    this->suit = suit;
}

//Getters for the Card object's point value and suit
string Card::getValue(){
    return this->value;
}
string Card::getSuit(){
    return this->suit;
}


string Card::print() {
    return (value + " of " + suit);
}
