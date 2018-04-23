// Created by Nick Azcarate on 4/15/18.

#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H
#include <iostream>
#include <vector>
#include "Player.h"
#include "DeckStack.h"
#include <thread>
using namespace std;

class Game {
private:
    int numPlayers = 2; //this number holds the number of people sitting across from the dealer (i.e. not including the dealer)
    int amountMoney;
    int tableBuyIn; // holds the minimum value that players must bet
    int userIndex;
    int numDecks = 4;
    vector<Player *> players;
    vector<Player *> outPlayers;
    DeckStack * unusedPile;
    DeckStack * discardPile;
    int lastRoundShuffled;
public:
    Game();
    void runPlayingMode();
	void startGame();
    void runSimulationMode();
    int determineUserIndex();
    void gamePlay();
    //vector<Player *> getPlayers();
    int getTableBuyIn();
    int getNumPlayers();
    int getAmountMoney();
    int getMinBet();
    void setNumPlayers(int num);
    void setAmountMoney(int num);
    void setTableBuyIn(int num);
    //void setNumDecks(int num);
    void discard(Card *);
    bool doPeopleHaveMoney();
    Player * findPlayer(int playerIdentity);
    int getNumDecks();
    void setNumDecks(int num);
	vector<Player *> getPlayers();
};


#endif //BLACKJACK_GAME_H
