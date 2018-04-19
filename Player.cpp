// Created by Nick Azcarate on 4/14/18.

#include "Player.h"
// implemented directly in takeTurn() for now
void Player::getCard() {
    // deal card
}

// may implement later
bool Player::doubleDown() {

}

// implemented directly in takeTurn() for now
void Player::stand() {

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

int Player::getPlayerIdentity(){
    return this->playerIdentity;
}

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

void Player::lostGame() {
    gamesLost++;
}

void Player::tiedGame() {
    gamesTied++;
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

        // FINISH implement other behaviors
        default:
            return randoTurn();
    }
}

// returns action
// Stops hitting at a hard 17. Will continue to hit if at a soft 17
int Player::dealerTurn(){
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

// Randomly chooses to get card, double down, stand, surrender, of split insurance
int Player::randoTurn(){
  int randNum = rand()%100 +1;
  if (randNum <= 70)      // 70% chance the bot will hit
        getCard();
    else if((randNum > 70) && (randNum <= 80))      // 10% chance the bot will stand
        stand();
    else if((randNum > 80) && (randNum <= 90))      // 10% chance the bot will surrender
        surrender();
    else if((randNum > 90) && (randNum <= 95))      // 5% chance the bot will double down
        doubleDown();
    else                                            // 5% chance the bot will purchase insurance
        purchaseInsurance();
}

int Player::superCardCounterTurn(){ // This person uses a card counting strategy, remembering ALL of the cards

}

int Player::weakCardCounterTurn()
{ // This person uses a card counting strategy, using the true count and run count to make betting decisions
// may use runCount and/or trueCount functions
// will use "illustrious 18" strategy outlined here https://www.888casino.com/blog/blackjack-strategy-guide/blackjack-card-counting
    runCount();
    trueCount(runningCount);
    int topCard = determineValue(dealer->hand.at(dealer->hand.size()-1)->getValue());       // gets dealer's top card
    int handTotal = getHandTotals().at(0);      // gets soft total for hand
    if ((handTotal == 16) && (topCard == 9) && (truCount >= 5))     // if your hand is 16, the dealer's top card is 9, and the true count is +5 or above
        stand();                                                          // stand
    else if ((handTotal == 16) && (topCard == 10) && (truCount >= 0))     // if your hand is 16, the dealer's top card is 10, and the true count is 0 or above)
        stand();
    else if ((handTotal == 15) && (topCard == 10) && (truCount >= 4))     // if your hand is 15, the dealer's top card is 10, and the true count is +4 or above)
        stand();
    else if ((handTotal == 13) && (topCard == 2) && (truCount >= -1))     // if your hand is 13, the dealer's top card is 2, and the true count is -1 or above)
        stand();
    else if ((handTotal == 13) && (topCard == 3) && (truCount >= -2))     // if your hand is 13, the dealer's top card is 3, and the true count is -2 or above)
        stand();
    else if ((handTotal == 12) && (topCard == 2) && (truCount >= 4))     // if your hand is 12, the dealer's top card is 2, and the true count is +4 or above)
        stand();
    else if ((handTotal == 12) && (topCard == 3) && (truCount >= 2))     // if your hand is 12, the dealer's top card is 3, and the true count is +2 or above)
        stand();
    else if ((handTotal == 12) && (topCard == 4) && (truCount >= 0))     // if your hand is 12, the dealer's top card is 4, and the true count is 0 or above)
        stand();
    else if ((handTotal == 12) && ((topCard == 5) || (topCard == 6)) && (truCount >= -1))     // if your hand is 12, the dealer's top card is a 5 or 6, and the true count is -1 or above)
        stand();
    else if ((handTotal == 11) && (topCard == 1) && (truCount >= 1))     // if your hand is 11, the dealer's top card is Ace, and the true count is +1 or above)
        doubleDown();
    else if ((handTotal == 10) && (topCard == 10) && (truCount >= 4))     // if your hand is 10, the dealer's top card is 10, Jack, Queen, or King, and the true count is +4 or above)
        doubleDown();
    else if ((handTotal == 10) && (topCard == 1) && (truCount >= 4))     // if your hand is 10, the dealer's top card is Ace, and the true count is +4 or above)
        doubleDown();
    else if ((handTotal == 9) && (topCard == 2) && (truCount >= 1))     // if your hand is 9, the dealer's top card is 2, and the true count is +1 or above)
        doubleDown();
    else if ((handTotal == 9) && (topCard == 7) && (truCount >= 4))     // if your hand is 9, the dealer's top card is 7, and the true count is +4 or above)
        doubleDown();
    else
        getCard();
}

void Player::runCount()      // adds or subtracts to the running count based on the current top cards on the table
{
    int topCard;
    for (Player * p : Game.players)
    {
        topCard = determineValue(p->hand.at(p->hand.size()-1)->getValue());     // sets the current top card value equal to the top card of the player in question
        if ((topCard >= 2) && (topCard <= 6))       // If the top card of the other player is b/w 2 and 6, add 1 to the running count
            runningCount++;
        else if((topCard == 10) || (topCard == 1))      // If the top card of the other player is a Jack, Queen, King, or Ace, subtract one from the running count
            runningCount--;
    }
    return;
}
void Player::trueCount(int runningCount)     // computes the true count by dividing the running count by the number of decks in play
{
    truCount = runningCount/DeckStack.numberDecks;
    return;
}
int Player::determineValue(string value)
{
    if (value == "A") {                     // If the card value is Ace, return a 1 as the int value
        return 1;
    }
    else if (value == "J" or value == "Q" or value == "K") {
        return 10;                   // if the card value is a Jack, Queen, or King, returns 10 as the int value
    }
    else {
        return stoi(value);          // All other cards return their card value, but in int form (which is what stoi() does)
    }
}
// This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
// strategy for hard totals
int Player::basicHardTurn(){
    string dealerTopCard = hand.at(hand.size()-1)->getValue();      // returns the card value on the hand of the dealer (assuming the top card is the last card in the hand)
    int dealerTopCardNumVal;                                        // creates an int variable to hold the int value of the card value (which is originally string)
    if (dealerTopCard == "A") {                     // If the card value is Ace, return a 1 as the int value
        dealerTopCardNumVal = 1;
    }
    else if (dealerTopCard == "J" or dealerTopCard == "Q" or dealerTopCard == "K") {
        dealerTopCardNumVal = 10;                   // if the card value is a Jack, Queen, or King, returns 10 as the int value
    }
    else {
        dealerTopCardNumVal = stoi(dealerTopCard);          // All other cards return their card value, but in int form (which is what stoi() does)
    }
    switch(getHandTotals().at(getHandTotals().size()-1)){        // gives the current card total
        case 17:                // always stand
            stand();
            break;
        case 16:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                stand();
            else
                getCard();
            break;
        case 15:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                stand();
            else
                getCard();
            break;
        case 14:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                stand();
            else
                getCard();
            break;
        case 13:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                stand();
            else
                getCard();
            break;
        case 12:                // stand if dealer's upcard is 4-6, hit if 2, 3, or 7-Ace
            if ((dealerTopCardNumVal >= 4) && (dealerTopCardNumVal <= 6))
                stand();
            else
                getCard();
            break;
        case 11:                // always double down
            doubleDown();
            break;
        case 10:                // double down if dealer's upcard is 2-9, hit if 10, face, or Ace
            if ((dealerTopCardNumVal >= 2 && dealerTopCardNumVal <= 9))
                doubleDown();
            else
                getCard();
            break;
        case 9:                 // double down if dealer's upcard is 3-6, hit if 2, or 7-Ace
            if ((dealerTopCardNumVal >= 3 && dealerTopCardNumVal <= 6))
                doubleDown();
            else
                getCard();
            break;
        default:                // always hit
            getCard();
    }
}

// This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
// strategy for soft totals
int Player::basicSoftTurn(){
    string dealerTopCard = hand.at(hand.size()-1)->getValue();      // returns the card value on the hand of the dealer (assuming the top card is the last card in the hand)
    int dealerTopCardNumVal;                                        // creates an int variable to hold the int value of the card value (which is originally string)
    if (dealerTopCard == "A") {                     // If the card value is Ace, return a 1 as the int value
        dealerTopCardNumVal = 1;
    }
    else if (dealerTopCard == "J" or dealerTopCard == "Q" or dealerTopCard == "K") {
        dealerTopCardNumVal = 10;                   // if the card value is a Jack, Queen, or King, returns 10 as the int value
    }
    else {
        dealerTopCardNumVal = stoi(dealerTopCard);          // All other cards return their card value, but in int form (which is what stoi() does)
    }
    switch(getHandTotals().at(0)){        // gives the current soft total
        case 20:                // always stand
            stand();
            break;
        case 19:                // doubles against dealer's 6, otherwise stands
            if (dealerTopCardNumVal == 6)
                doubleDown();
            else
                stand();
            break;
        case 18:                // doubles against dealer's 2 through 6, and hits against 9 through Ace, otherwise stands
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                doubleDown();
            else if((dealerTopCardNumVal == 9) || (dealerTopCardNumVal == 10) || (dealerTopCardNumVal == 1))
                getCard();
            else
                stand();
            break;
        case 17:                // doubles against dealer's 3 through 6, otherwise hits
            if ((dealerTopCardNumVal >= 3) && (dealerTopCardNumVal <= 6))
                doubleDown();
            else
                getCard();
            break;
        case 16:                //doubles against dealer's 4 through 6, otherwise hits
            if ((dealerTopCardNumVal >= 4) && (dealerTopCardNumVal <= 6))
                doubleDown();
            else
                getCard();
            break;
        case 15:                //doubles against dealer's 4 through 6, otherwise hits
            if ((dealerTopCardNumVal >= 4) && (dealerTopCardNumVal <= 6))
                doubleDown();
            else
                getCard();
            break;
        case 14:                // doubles against dealer's 5 or 6, otherwise hits
            if ((dealerTopCardNumVal == 5) || (dealerTopCardNumVal == 6))
                doubleDown();
            else
                getCard();
            break;
        case 13:                // doubles against dealer's 5 or 6, otherwise hits
            if ((dealerTopCardNumVal == 5) || (dealerTopCardNumVal == 6))
                doubleDown();
            else
                getCard();
            break;
        default:                // always hit if none of the above options are satisfied
            getCard();
    }
}

void updateMoney(int difference){
  
}

void Player::giveCard(Card * card) {
    hand.push_back(card);
}

vector<int> Player::getHandTotals() {
    int aceCount = 0;
    int baseTotal = 0;
    for (Card * card : hand) {
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
    if(aceCount >= 1){ //if there is 1 or more aces, add 10 to the total
        //note that in Blackjack, only 1 ace can be 11 (in a hand with multiple), the remainder are 1s
        totals.push_back(baseTotal + 10);
    }

    // removes totals that cause a bust (greater than 21)
    while (totals.size() > 1 && totals.at(totals.size() - 1) > 21) {
        totals.pop_back();
    }
    return totals;
}

int Player::getBestHand() {
    vector<int> totals = getHandTotals();
    int best = totals.at(0);
    //find the hand with the greatest value that is less than or equal to 21
    for (int i : totals) {
        if (i > best && i <= 21)
            best = i;
    }
    return best;
}

// gets the user's bet
// add minimum?
// default bet $15?
int Player::getBet() {
    if(playerIdentity == 0) {
        cout << "You currently have $" << money << "."<< endl;
        int bet = 0;
        while (bet <= 15 || bet > money ) {
            cout <<  "How much money would you like to bet? ";
            cin >> bet;
            if (bet <= 0) {
                cout << "Invalid input - bet must be a positive integer.\n\n";
            }
            else if(bet < 15){
               cout << "Invalid input - table minimum bet is $15.\n\n";
            }
            else if (bet > money) {
                cout << "Invalid input - insufficient funds.\n\n";
            }
        }
        return bet;
    }
    else if (playerIdentity == 1) {
        return 0;
    }
    else {
        return 15;
    }
}