/*
 * Game.cpp
 *
 * by Nicolas Azcarate, Gregory DeCanio, Asher Johnson Hogan,
 * Colby Lathrop, Spencer Warren, and Davis Washburn
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
    vector<int> bets; //stores player's bets
    vector<bool> surrendered;
    void stand(Player * p);
    void hit(Player * p);
    void doubleDown(Player * p);
    void surrender(Player * p);
    Player * findPlayer(int playerIdentity);
    int findPlayerSeat(Player * p);

};


#endif //BLACKJACK_GAME_H
