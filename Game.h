// Created by Nick Azcarate on 4/15/18.

#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H
using namespace std;
#include <iostream>
#include <vector>
#include "Player.h"
#include "DeckStack.h"


class Game {
private:
    int numPlayers;
    int amountMoney;
    int tableBuyIn;
    vector<Player *> players;
    DeckStack * deck;
    vector<Card *> discard;
public:
    Game(int userGameTypeChoice, int tableBuyIn);
    void runPlayingMode();
    void runSimulationMode();
    void gamePlay();
    vector<Player *> getPlayers();
    int getTableBuyIn();
    int getNumPlayers();
    int getAmountMoney();
};


#endif //BLACKJACK_GAME_H
