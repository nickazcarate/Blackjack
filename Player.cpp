// Created by Nick Azcarate on 4/14/18.

#include "Player.h"

Player::Player(int money, int playerIdentity, const Game* game) : game(game){
    this->money = money;
    this->playerIdentity = playerIdentity;
    gamesWon = 0;
    gamesLost = 0;
    gamesTied = 0;
}

int Player::getMoney(){
    return this->money;
}

vector<Card*> Player::getHand(){
    return this->hand;
}

void Player::wonGame() {
    gamesWon++;
}

void Player::tiedGame() {
    gamesTied++;
}

void Player::lostGame() {
    gamesLost++;
}

int Player::getWins() {
    return gamesWon;
}

int Player::getLosses() {
    return gamesLost;
}

int Player::getTies() {
    return gamesTied;
}

vector<int> Player::getHandTotals() {
    int aceCount = 0;
    int baseTotal = 0;
    for (Card* card : hand) {
        string value = card->getValue();
        if (value == "A") {
            aceCount++;
            baseTotal += 1;
        }
        else if (value == "J" or value == "Q" or value == "K") {
            baseTotal += 10;
        }
        else {
            baseTotal += stoi(value);
        }
    }
    vector<int> totals;
    totals.push_back(baseTotal);
    for (int i = 1; i <= aceCount; i++) {
        totals.push_back(baseTotal + 9 * i);
    }
    return totals;
}

void Player::takeTurn() {
    if (!isBot) {
        cout << "What would you like to do?";
    }
}

void Player::dealerTurn()
{

}
void Player::randoTurn()
{

}
void Player::superCardCounterTurn()
{

}
void Player::weakCardCounterTurn()
{

}
void Player::basicHardTurn()
{

}
void Player::basicSoftTurn()
{

}

void Player::getCard() {
    // deal card
}

bool Player::doubleDown() {

}

void Player::stand() {

}

void Player::surrender() {

}

// may implement later
bool Player::split() {
    return false;
}

void Player::purchaseInsurance() {

}