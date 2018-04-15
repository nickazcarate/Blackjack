using namespace std;
#include <iostream>
#include "Card.h"
#include "DeckStack.h"
#include "Game.h"
#include <thread>
#include <chrono>


int numPlayers = 0;
int userGameTypeChoice = 0;

int beginMenu(){
    cout << "\nWelcome to Blackjack!\n\n";
    this_thread::sleep_for(chrono::milliseconds(600));
    cout << "You may run either:\n";
    cout << "\t 1) Playing mode: play rounds of Blackjack against a dealer and other players\n";
    cout << "\t 2) Simulation mode: run many simulations to test effectiveness of playing styles between our bots\n";
    cout << "Enter 1 or 2: ";
    cin >> userGameTypeChoice;
}

int main() {
    //beginMenu();
    //Game * game = new Game(userGameTypeChoice, 100);

    DeckStack * unusedCards = new DeckStack(1); //creates a deckstack with 1 deck, shuffled
    unusedCards->printDeck();
    cout << "Top card is " << unusedCards->getTopCard()->getValue() << " of " << unusedCards->getTopCard()->getSuit() << endl;
    cout << "Now I'll remove the top card and print the new top card" << endl;
    unusedCards->removeTopCard();
    cout << "Top card is " << unusedCards->getTopCard()->getValue() << " of " << unusedCards->getTopCard()->getSuit() << endl;
    unusedCards->printDeck();


    //num players (meaning not the dealer, other than you) dealer always exists
        //max players of 5 other than the user running code
        //could enter 0 to mean you want to play just you and dealer
        //3 means that you want to play alongside 3 other people (total of 4 players, and the dealer)
    //always use 6 decks
    //starting cash (for every player) given that dealer has infinite money




}