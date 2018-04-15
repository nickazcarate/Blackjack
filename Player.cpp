// Created by Nick Azcarate on 4/14/18.

#include "Player.h"

Player::Player(int money, bool isBot, const Game* game) : game(game){
    this->money = money;
    this->isBot = isBot;
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


void takeTurn();
void updateMoney();

void getCard();
void doubleDown();
void stand();
void surrender();
void split();
void purchaseInsurance();

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

void Player::doubleDown() {

}

void Player::stand() {

}

void Player::surrender() {

}

bool Player::split() {
    return true;
}

void Player::purchaseInsurance() {

}