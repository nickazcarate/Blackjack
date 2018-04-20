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


int Card::getNumericValue()
{
    if (value == "A") {                     // If the card value is Ace, return a 1 as the int value
        return 1;
    }
    else if (value == "J" or value == "Q" or value == "K") {
        return 10;                   // if the card value is a Jack, Queen, or King, returns 10 as the int value
    }
    else {
        return stoi(value);          // All other cards return their card value, but in int form (which is what stoi() does)
    }
}