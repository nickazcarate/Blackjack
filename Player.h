// Created by Nick Azcarate on 4/14/18.

#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H
using namespace std;
#include <iostream>
#include "Card.h"
#include "DeckStack.h"
#include <vector>


class Player {
private:
    int money;
    int gamesWon;
    int gamesLost;
    int gamesTied;
    bool hasNatural;
    vector<Card *> hand;
    int playerIdentity;
        // 0 = user, 1 = random choices, 2 = incredible card counter, 3 = pretty good card counter,
        // 4 = basic card strategy SOFT , 5 = basic card strategy hard;), 6 = dealer
    int getCard();
    int doubleDown();
    int stand();
    int surrender();
    bool split();
    void purchaseInsurance();
    double getProbability(int cardValue);
    int truCount;
    vector<Card *> rememberedDiscards; // used by identity 2 (super card counter)
    int discardTally; // keeps a running count of the +/- card values on the table (for the reg card counter)
    int numDecks;
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
    bool getNatural();
    void setNatural(bool value);
    int takeTurn(Card * dealersTop);
    int dealerTurn();              // Stops hitting at a hard 17. Will hit once more if at a soft 17
    int randoTurn();               // Randomly chooses to get card, double down, stand, surrender, of split insurance
    int superCardCounterTurn(Card * dealersTop);    // This person uses a card counting strategy, remembering ALL of the cards
    int weakCardCounterTurn(Card * dealersTop);     // This person uses a card counting strategy, remembering only the previous 10 cards
    void trueCount();        // computes the true count of cards played so far (run count / num decks)
    int basicHardTurn(Card * dealersTop);    // This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
                            // strategy for hard totals
    int basicSoftTurn(Card * dealersTop);    // This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
                            // strategy for hard totals
    void updateMoney(int difference);
    void giveCard(Card *);
    int getBet(int tableBuyIn);
    int getPlayerIdentity();
    vector<int> getHandTotals();
    int getBestHand();
    void cardCount(Card *);
    void resetCounting();
    void setNumDecks(int numDecks);
    void clearHand();
};


#endif //BLACKJACK_PLAYER_H
