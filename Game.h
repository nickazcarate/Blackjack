/*
 * Game.cpp
 *
 * by Asher Johnson Hogan, Nicolas Azcarate, Gregory DeCanio
 * Davis Washburn, Colby Lathrop, and Spencer Warren
 */

#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "DeckStack.h"
#include <thread>
using namespace std;

//Initialize the Game class and its respective functions
class Game {
private:

    //this number holds the number of people sitting across from the dealer (i.e. not including the dealer)
    int numPlayers;
    int amountMoney;

    // holds the minimum value that players must bet
    int tableBuyIn;
    int userIndex;
    vector<Player *> players;
    vector<Player *> outPlayers;
    DeckStack * unusedPile;
    DeckStack * discardPile;
    int lastRoundShuffled;

public:

    Game(int userGameTypeChoice);
    void runPlayingMode();
    void runSimulationMode();
    int determineUserIndex();
    void gamePlay();
    vector<Player *> getPlayers();
    int getTableBuyIn();
    void getNumPlayers();
    void getAmountMoney();
    void getMinBet();
    void discard(Card *);
    bool doPeopleHaveMoney();
    Player * findPlayer(int playerIdentity);

};


#endif //BLACKJACK_GAME_H
