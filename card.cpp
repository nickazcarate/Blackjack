// Created by Nick Azcarate on 4/14/18.

#include "Card.h"



	// Constructor for the Card Object
	Card::Card(string value, string suit) {

		this->value = value;
		this->suit = suit;
	}

	// Getter for a card's point value
	string Card::getValue() {
		return this->value;
	}

	// Getter for a card's suit (for GUI purposes)
	string Card::getSuit() {
		return this->suit;
	}

	// Getter for a cards point value in blackjack (A being 11 or 1 depending on the hand, and the face cards all being 10), as an int
	int Card::getNumericValue() {

		// If the card value is Ace, return a 1 as the int value
		if (value == "A") {
			return 1;
		}

		// if the card value is a Jack, Queen, or King, returns 10 as the int value
		else if (value == "J" || value == "Q" || value == "K") {
			return 10;
		}
		else {

			// All other cards return their card value, but in int form (which is what stoi() does)
			return stoi(value);
		}
	}
