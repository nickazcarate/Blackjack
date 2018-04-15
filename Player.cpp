// Created by Nick Azcarate on 4/14/18.

#include "Player.h"

Player::Player(int money, bool isBot) {
    this->money = money;
    this->isBot = isBot;
}
int Player::getMoney(){
    return this->money;
}
vector<Card *> Player::getHand(){
    return this->hand;
}