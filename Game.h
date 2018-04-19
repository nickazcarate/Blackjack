// Created by Nick Azcarate on 4/15/18.

#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H
using namespace std;
#include <iostream>
#include <vector>
#include "Player.h"
#include "DeckStack.h"
#include <thread>


class Game {
private:
    int numPlayers;
    int amountMoney;
    int tableBuyIn; // holds the minimum value that players must bet
    int userIndex;
    vector<Player *> players;
    DeckStack * unusedPile;
    DeckStack * discardPile;
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
};


#endif //BLACKJACK_GAME_H
