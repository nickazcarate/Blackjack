// Created by Nick Azcarate on 4/14/18.

#include "Player.h"

Player::Player(int money, int playerIdentity){
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
    // removes totals that can't be used (greater than 21)
    while (totals.size() > 1 and totals.at(totals.size() - 1) > 21) {
        totals.pop_back();
    }
    return totals;
}

void Player::giveCard(Card * card) {
    hand.push_back(card);
}

// will return the user's choice so game can use it
int Player::takeTurn(Card * dealersTop) {
    switch (playerIdentity) {
        case 0: {
            cout << "The dealer's top card is " << dealersTop->print();
            bool goodInput = false;
            int input;
            while (!goodInput) {
                cout << "\nYour current hand is";
                for (Card *c : hand) {
                    cout << " " << c->getValue();
                }
                cout << "\nWhat would you like to do? (0 for stand, 1 for hit): ";
                string temp;
                cin >> temp;
                if (temp == "1" or temp == "0") {
                    goodInput = true;
                    input = temp == "0" ? 0 : 1;
                } else {
                    cout << "Invalid input. Please enter 0 or 1\n";
                }
            }
            return input;
        }

        case 1:
            return dealerTurn();

        // implement other behaviors
        default:
            return randoTurn();

    }

}

// returns action
int Player::dealerTurn() // Stops hitting at a hard 17. Will continue to hit if at a soft 17
{
    if(getHandTotals().at(getHandTotals().size()-1) >= 17)
    {
        // Add that the dealer is standing (a prefix)
        return 0;
    }
    else
    {
        // Add that the dealer is hitting (a prefix)
        return 1;
    }
}
int Player::randoTurn() // Randmomly chooses to get card, double down, stand, surrender, of split insurance
{
int randNum = rand()%100 +1;
    if (randNum <= 70)      // 70% chance the bot will hit
    {
        getCard();
    }
    else if((randNum > 70) && (randNum <= 80))      // 10% chance the bot will stand
    {
        stand();
    }
    else if((randNum > 80) && (randNum <= 90))      // 10% chance the bot will surrender
    {
        surrender();
    }
    else if((randNum > 90) && (randNum <= 95))      // 5% chance the bot will double down
    {
        doubleDown();
    }
    else                                            // 5% chance the bot will purchase insurance
    {
        purchaseInsurance();
    }
}
int Player::superCardCounterTurn() // This person uses a card counting strategy, remembering ALL of the cards
{

}
int Player::weakCardCounterTurn() // This person uses a card countring strategy, remembering only the previous 10 cards
{

}
int Player::basicHardTurn()    // This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
                                // strategy for hard totals
{

    switch(getHandTotals().at(getHandTotals().size()-1))        // gives the current card total
    {
        case 17:                // always stand
            stand();
            break;
        case 16:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            break;
        case 15:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            break;
        case 14:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            break;
        case 13:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            break;
        case 12:                // stand if dealer's upcard is 4-6, hit if 2, 3, or 7-Ace
            break;
        case 11:                // always double down
            break;
        case 10:                // double down if dealer's upcard is 2-9, hit if 10, face, or Ace
            break;
        case 9:                 // double down if dealer's upcard is 3-6, hit if 2, or 7-Ace
            break;
        default:                // always hit
            getCard();
    }
}
int Player::basicSoftTurn()    // This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
                                // strategy for soft totals
{

}

// implemented directly in takeTurn() for now
void Player::getCard() {
    // deal card
}

// implemented directly in takeTurn() for now
void Player::stand() {

}

// may implement later
bool Player::doubleDown() {

}

// may implement later
void Player::surrender() {

}

// may implement later
bool Player::split() {
    return false;
}

// may implement later
void Player::purchaseInsurance() {

}