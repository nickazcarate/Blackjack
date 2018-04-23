/*
 * Player.h
 *
 * by Nicolas Azcarate, Gregory DeCanio, Asher Johnson Hogan,
 * Colby Lathrop, Spencer Warren, and Davis Washburn
 */

#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H

#include <iostream>
#include "Card.h"
#include "DeckStack.h"
#include <vector>
using namespace std;

class Player {
private:
    int money;
    int gamesWon;
    int gamesLost;
    int gamesTied;
    bool hasNatural;
    bool endTurn;
    vector<Card *> hand;
    string playerName;
    int playerIdentity;
        // 0 = user, 1 = random choices, 2 = incredible card counter, 3 = pretty good card counter,
        // 4 = basic card strategy SOFT , 5 = basic card strategy hard;), 6 = dealer
    int stand();
    int getCard();
    int doubleDown();
    int surrender();
    double getProbability(int cardValue);
    double trueCount;
    vector<Card *> rememberedDiscards; // used by identity 2 (super card counter)
    double runningCount; // keeps a running count of the +/- card values on the table (for the reg card counter)
    int discardTally;
    int numDecks;
    int curBet; // stores the player's most recent bet to see if they can double down

public:
    Player(int money, int playerIdentity, string name);
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
    void updateTrueCount();        // computes the true count of cards played so far (run count / num decks)
    int basicHardTurn(Card * dealersTop);    // This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
                            // strategy for hard totals
    int basicSoftTurn(Card * dealersTop);    // This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
                            // strategy for hard totals
    void updateMoney(int difference);
    void giveCard(Card *);
    int getBet(int tableBuyIn);
    int getPlayerIdentity();
    string getPlayerName();
    vector<int> getHandTotals();
    int getBestHand();
    void cardCount(Card *);
    void resetCounting();
    void setNumDecks(int numDecks);
    void setEndTurn(bool value);
    bool getEndTurn();
    void clearHand();
    bool canBet(int bet);
    void printHand();
    void printTop();
};

#endif //BLACKJACK_PLAYER_H
