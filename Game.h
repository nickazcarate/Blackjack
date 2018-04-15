// Created by Nick Azcarate on 4/15/18.

#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H
using namespace std;
#include <iostream>
#include "Player.h"
#include <vector>


class Game {
public:
    Game(int userGameTypeChoice, int tableBuyIn);
    void runPlayingMode();
    void runSimulationMode();
    void gamePlay();
    vector<Player *> getPlayers();
    int getTableBuyIn();
    void getNumPlayers();
    void getAmtMoney();
private:
    int numPlayers;
    int amtMoney;
    int tableBuyIn;
    vector<Player *> players;
};


#endif //BLACKJACK_GAME_H
