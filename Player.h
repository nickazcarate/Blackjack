// Created by Nick Azcarate on 4/14/18.

#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H
#include "Card.h"
#include "Game.h"
#include <vector>


class Player {
public:
    Player(int money, bool isBot, const Game* game);
    int getMoney();
    vector<Card *> getHand();
    void wonGame();
    void lostGame();
    void tiedGame();
    int getWins();
    int getLosses();
    int getTies();
    void takeTurn();
    void updateMoney();
private:
    const Game* game;
    int money;
    int gamesWon;
    int gamesLost;
    int gamesTied;
    vector<Card *> hand;
    bool isBot;
    void getCard();
    void doubleDown();
    void stand();
    void surrender();
    bool split();
    void purchaseInsurance();
};


#endif //BLACKJACK_PLAYER_H
