// Created by Nick Azcarate on 4/14/18.

#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H
using namespace std;
#include <iostream>
#include "Card.h"
#include <vector>


class Player {
public:
    Player(int money, int playerIdentity);
    int getMoney();
    vector<Card *> getHand();
    void wonGame();
    void lostGame();
    void tiedGame();
    int getWins();
    int getLosses();
    int getTies();
    void takeTurn();
    void dealerTurn();              // Stops hitting at a hard 17. Will hit once more if at a soft 17
    void randoTurn();               // Randomly chooses to get card, double down, stand, surrender, of split insurance
    void superCardCounterTurn();    // This person uses a card counting strategy, remembering ALL of the cards
    void weakCardCounterTurn();     // This person uses a card counting strategy, remembering only the previous 10 cards
    void basicHardTurn();   // This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
                            // strategy for hard totals
    void basicSoftTurn();   // This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
                            // strategy for hard totals
    void updateMoney();
    vector<int> getHandTotals();
private:
    int money;
    int gamesWon;
    int gamesLost;
    int gamesTied;
    vector<Card *> hand;
    int playerIdentity; // 0 = user, 1 = dealer, 2 = random choices, 3 = incredible card counter, 4 = pretty good card counter, 5 = basic card strategy,
    void getCard();
    bool doubleDown();
    void stand();
    void surrender();
    bool split();
    void purchaseInsurance();
};


#endif //BLACKJACK_PLAYER_H
