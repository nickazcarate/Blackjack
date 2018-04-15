// Created by Nick Azcarate on 4/14/18.

#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H
#include "Card.h"
#include <vector>


class Player {
public:
    Player(int money, bool isBot);
    int getMoney();
    vector<Card *> getHand();
    void wonGame();
    void lostGame();
    void tiedGame();
private:
    int money;
    int gamesWon;
    int gamesLost;
    int gamesTied;
    vector<Card *> hand;
    bool isBot;

};


#endif //BLACKJACK_PLAYER_H
