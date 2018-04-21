// Created by Nick Azcarate on 4/14/18.

#include "Player.h"

// #include "Game.h"


// implemented directly in takeTurn() for now
int Player::getCard() {    // deal card
    return 1;
}

// may implement later
int Player::doubleDown() {
    return 2;
}

// implemented directly in takeTurn() for now
int Player::stand() {
    return 0;
}

// may implement later
int Player::surrender() {
    return 3;
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


// sets numDecks, called once by Game before the game starts
void Player::setNumDecks(int numDecks) {
    this->numDecks = numDecks;
}

//Check probability that a card of a specified value would be drawn
double Player::getProbability(int cardValue) {

    double probability = 0;
    int deckCount = numDecks; // call the getter for numberDecks within DeckStack
    int cardValCount = 0;

    for (Card * card : rememberedDiscards) {

       //Grabs value of the card in the current space in rememberedDiscards
       int testValue = card->getNumericValue();

       //If the current card is the same as the requested value,
       if (testValue == cardValue) {
            cardValCount++;
       }
    }

    if (cardValue == 10) {

        //probability = number of cards of specified value remaining divided by total cards that are left
        // 16 = number of Jacks, Queens, Kings, and 10s in one deck of cards
        probability = (double)((16*deckCount)-cardValCount)/(double)((deckCount*52)-rememberedDiscards.size());
    }
    else {

        //probability = number of cards of specified value remaining divided by total cards that are left
        probability = (double)((4*deckCount)-cardValCount)/(double)((deckCount*52)-rememberedDiscards.size()); //
    }

    return probability;
}

// will return the user's choice so game can use it
int Player::takeTurn(Card * dealersTop) {
    switch (playerIdentity) {
        case 0: {
            int input;
            while (true) {
                cout << "\nYour current hand is";
                for (Card *c : hand) {
                    cout << " " << c->getValue();
                }
                cout << "\n\nWhat would you like to do? (1 for stand, 2 for hit, 3 for double down, 4 for surrender): ";
                string temp;
                cin >> temp;
                if (temp == "1" or temp == "2" or temp == "3" or temp == "4") {
                    input = stoi(temp) + 1;
                    return input;
                }
                else {
                    cout << "Invalid input. Please enter 0 or 1\n";
                }
            }
        }

        case 1:
            return randoTurn();
        case 2:
            return superCardCounterTurn(dealersTop);
        case 3:
            return weakCardCounterTurn(dealersTop);
        case 4:
            return basicSoftTurn(dealersTop);
        case 5:
            return basicHardTurn(dealersTop);
        case 6:
            return dealerTurn();
        default:
            return randoTurn();
    }
}

// Stops hitting at a hard 17. Will continue to hit if at a soft 17
int Player::dealerTurn(){
    if(getHandTotals().at(0) >= 17)
    {
        return stand();
    }
    else
    {
        return getCard();
    }
}

// Randomly chooses to get card, double down, stand, surrender, of split insurance
int Player::randoTurn(){
    int randNum = rand()%100 +1;
    if (randNum <= 70)                                // 70% chance the bot will hit
        return getCard();
    else                                            // 30% chance the bot will stand
        return stand();
      /*
    else if((randNum > 80) && (randNum <= 90))      // 10% chance the bot will surrender
        return surrender();
    else if((randNum > 90) && (randNum <= 95))      // 5% chance the bot will double down
        return doubleDown();
    else                                            // 5% chance the bot will purchase insurance
        return purchaseInsurance();
        */
}

// This person uses a card counting strategy, remembering ALL of the cards
int Player::superCardCounterTurn(Card * dealersTop) {

    int topCard = dealersTop->getNumericValue();       // gets dealer's top card
    int handValue = getBestHand();
    double bustChance = 0;
    double safeChance = 0;
    double riskValue = 0;
    int twentyOneChance = getProbability(21-handValue);

    //The bot plays riskier depending on the card the dealer shows. With Ace being the riskiest and
    if (topCard == 1) {
        riskValue = 6;
    }
    else if (topCard == 10) {
        riskValue = 5;
    }
    else if (topCard == 9 || topCard == 8) {
        riskValue = 4;
    }
    else {
        riskValue = 3;
    }
    for (int i = 1; i <= 10; i++) {
        if (i + handValue <= 21) {
            safeChance += getProbability(i);
        }
        else {
            bustChance += getProbability(i);
        }
    }

    //check if chance for doubling down into 21 is good enough, if so double down
    if (twentyOneChance > bustChance) {
        return doubleDown();
    }
    else if (bustChance < riskValue/10) {
        return getCard();
    }
    else {
        return stand();
    }

}
/*
int Player::weakCardCounterTurn(Card * dealersTop) {

// This person uses a card counting strategy, using the true count and run count to make betting decisions
// may use runCount and/or trueCount functions
// will use "illustrious 18" strategy outlined here https://www.888casino.com/blog/blackjack-strategy-guide/blackjack-card-counting
    trueCount();
    int topCard = dealersTop->getNumericValue();       // gets dealer's top card
    int handTotal = getHandTotals().at(0);      // gets soft total for hand
    if ((handTotal == 16) && (topCard == 9) && (truCount >= 5))     // if your hand is 16, the dealer's top card is 9, and the true count is +5 or above
        return stand();                                                          // stand
    else if ((handTotal == 16) && (topCard == 10) && (truCount >= 0))     // if your hand is 16, the dealer's top card is 10, and the true count is 0 or above)
        return stand();
    else if ((handTotal == 15) && (topCard == 10) && (truCount >= 4))     // if your hand is 15, the dealer's top card is 10, and the true count is +4 or above)
        return stand();
    else if ((handTotal == 13) && (topCard == 2) && (truCount >= -1))     // if your hand is 13, the dealer's top card is 2, and the true count is -1 or above)
        return stand();
    else if ((handTotal == 13) && (topCard == 3) && (truCount >= -2))     // if your hand is 13, the dealer's top card is 3, and the true count is -2 or above)
        return stand();
    else if ((handTotal == 12) && (topCard == 2) && (truCount >= 4))     // if your hand is 12, the dealer's top card is 2, and the true count is +4 or above)
        return stand();
    else if ((handTotal == 12) && (topCard == 3) && (truCount >= 2))     // if your hand is 12, the dealer's top card is 3, and the true count is +2 or above)
        return stand();
    else if ((handTotal == 12) && (topCard == 4) && (truCount >= 0))     // if your hand is 12, the dealer's top card is 4, and the true count is 0 or above)
        return stand();
    else if ((handTotal == 12) && ((topCard == 5) || (topCard == 6)) && (truCount >= -1))     // if your hand is 12, the dealer's top card is a 5 or 6, and the true count is -1 or above)
        return stand();
    else if ((handTotal == 11) && (topCard == 1) && (truCount >= 1))     // if your hand is 11, the dealer's top card is Ace, and the true count is +1 or above)
        return doubleDown();
    else if ((handTotal == 10) && (topCard == 10) && (truCount >= 4))     // if your hand is 10, the dealer's top card is 10, Jack, Queen, or King, and the true count is +4 or above)
        return doubleDown();
    else if ((handTotal == 10) && (topCard == 1) && (truCount >= 4))     // if your hand is 10, the dealer's top card is Ace, and the true count is +4 or above)
        return doubleDown();
    else if ((handTotal == 9) && (topCard == 2) && (truCount >= 1))     // if your hand is 9, the dealer's top card is 2, and the true count is +1 or above)
        return doubleDown();
    else if ((handTotal == 9) && (topCard == 7) && (truCount >= 4))     // if your hand is 9, the dealer's top card is 7, and the true count is +4 or above)
        return doubleDown();
    else
        return getCard();
}
*/
// This person uses a card counting strategy, using the true count and run count to make betting decisions
// Uses "illustrious 18" strategy outlined here https://www.888casino.com/blog/blackjack-strategy-guide/blackjack-card-counting
int Player::weakCardCounterTurn(Card *dealersTop) {
    trueCount();
    int topCard = dealersTop->getNumericValue();            // gets dealer's top card
    int handTotal = getHandTotals().at(0);                  // gets soft total for hand
    switch (handTotal)
    {
        case 16:                                            // if your hand is 16
            if ((topCard == 10) && (truCount >= 0))         // the dealer's top card is 9, and the true count is +5 or above
                return stand();
            else if ((topCard == 9) && (truCount >= 5))     // the dealer's top card is 10, Jack, Queen, or King, and the true count is 0 or above
                return stand();
            else
                return getCard();
        case 15:                                            // if your hand is 15
            if ((topCard == 10) && (truCount >= 4))         // the dealer's top card is 10, Jack, Queen, or King, and the true count is +4 or above
                return stand();
            else getCard();
        case 13:                                            // if your hand is 13
            if ((topCard == 2) && (truCount >= -1))         // the dealer's top card is 2, and the true count is -1 or above
                return stand();
            else if ((topCard == 3) && (truCount >= -2))    // the dealer's top card is 3, and the true count is -2 or above
                return stand();
            else
                return getCard();
        case 12:                                            // if your hand is 12
            if ((topCard == 2) && (truCount >= 4))
                return stand();
            else if ((topCard == 3) && (truCount >= 2))     // the dealer's top card is 3, and the true count is +2 or above
                return stand();
            else if ((topCard == 4) && (truCount >= 0))     // the dealer's top card is 4, and the true count is 0 or above
                return stand();
            else if (((topCard == 5) || (topCard == 6)) && (truCount >= -1))         // the dealer's top card is a 5 or 6, and the true count is -1 or above
                return stand();
            else
                return getCard();
        case 11:                                            // if your hand is 11
            if ((topCard == 1) && (truCount >= 1))          // the dealer's top card is an Ace, and the true count is +1 or above
                return doubleDown();
            else
                return getCard();
        case 10:                                            // if your hand is 10
            if ((topCard == 10) && (truCount >= 4))         // the dealer's top card is 10, Jack, Queen, or King, and the true count is +4 or above
                return doubleDown();
            else if ((topCard == 1) && (truCount >= 4))     // the dealer's top card is an Ace, and the true count is +4 or above
                return doubleDown();
            else
                return getCard();
        case 9:                                            // if your hand is 9
            if ((topCard == 2) && (truCount >= 1))         // the dealer's top card is 2, and the true count is +1 or above
                return doubleDown();
            else if ((topCard == 7) && (truCount >= 4))    // the dealer's top card is 7, and the true count is +4 or above
                return doubleDown();
            else
                return getCard();
        default:
            if (handTotal >= 17)                           // if your hand is 17
                return stand();                            // stand
            else                                           // if your hand is 14, or 8 and lower
                return getCard();                          // hit
    }
}
void Player::trueCount()     // computes the true count by dividing the running count by the number of decks in play
{
    truCount = discardTally/numDecks;
}


// This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
// strategy for hard totals
int Player::basicHardTurn(Card * dealersTop){
    int dealerTopCardNumVal = dealersTop->getNumericValue();        // returns the dealer's top card value
    int handTotal = getHandTotals().at(getHandTotals().size()-1);
    switch(handTotal){        // gives the current card total
        case 16:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 15:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 14:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 13:                // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 12:                // stand if dealer's upcard is 4-6, hit if 2, 3, or 7-Ace
            if ((dealerTopCardNumVal >= 4) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 11:                // always double down
            return doubleDown();
        case 10:                // double down if dealer's upcard is 2-9, hit if 10, face, or Ace
            if ((dealerTopCardNumVal >= 2 && dealerTopCardNumVal <= 9))
                return doubleDown();
            else
                return getCard();
        case 9:                 // double down if dealer's upcard is 3-6, hit if 2, or 7-Ace
            if ((dealerTopCardNumVal >= 3 && dealerTopCardNumVal <= 6))
                return doubleDown();
            else
                return getCard();
        default:
            if (handTotal >= 17)        // if the hand total is 17 or higher
                return stand();         // stand
            else                        // if the hand total is 8 or lower
                return getCard();       // hit
    }
}

// This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
// strategy for soft totals
int Player::basicSoftTurn(Card * dealersTop){
    int dealerTopCardNumVal = dealersTop->getNumericValue();
    int handTotal = getHandTotals().at(0);
    switch(handTotal){        // gives the current soft total
        case 19:                // doubles against dealer's 6, otherwise stands
            if (dealerTopCardNumVal == 6)
                return doubleDown();
            else
                return stand();
        case 18:                // doubles against dealer's 2 through 6, and hits against 9 through Ace, otherwise stands
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return doubleDown();
            else if((dealerTopCardNumVal == 9) || (dealerTopCardNumVal == 10) || (dealerTopCardNumVal == 1))
                return getCard();
            else
                return stand();
        case 17:                // doubles against dealer's 3 through 6, otherwise hits
            if ((dealerTopCardNumVal >= 3) && (dealerTopCardNumVal <= 6))
                return doubleDown();
            else
                return getCard();
        case 16:                //doubles against dealer's 4 through 6, otherwise hits
            if ((dealerTopCardNumVal >= 4) && (dealerTopCardNumVal <= 6))
                return doubleDown();
            else
                return getCard();
        case 15:                //doubles against dealer's 4 through 6, otherwise hits
            if ((dealerTopCardNumVal >= 4) && (dealerTopCardNumVal <= 6))
                return doubleDown();
            else
                return getCard();
        case 14:                // doubles against dealer's 5 or 6, otherwise hits
            if ((dealerTopCardNumVal == 5) || (dealerTopCardNumVal == 6))
                return doubleDown();
            else
                return getCard();
        case 13:                // doubles against dealer's 5 or 6, otherwise hits
            if ((dealerTopCardNumVal == 5) || (dealerTopCardNumVal == 6))
                return doubleDown();
            else
                return getCard();
        default:
            if (handTotal >= 20)        // if hand it 20 or higher
                return stand();         // stand
            else                        // if hand is 12 or lower
                return getCard();       // hit
    }
}

void Player::updateMoney(int difference){
    money += difference;
}

void Player::giveCard(Card * card) {
    hand.push_back(card);
}

vector<int> Player::getHandTotals() {
    bool hasAce = false;
    int baseTotal = 0;
    for (Card * card : hand) {
        int value = card->getNumericValue();
        if (value == 1) {
            hasAce = true;
            baseTotal += 1;
        }
        else {
            baseTotal += value;
        }
    }
    vector<int> totals;
    totals.push_back(baseTotal);
    if(hasAce){ //if there is 1 or more aces, add 10 to the total
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
int Player::getBet(int tableBuyIn) {
    if(playerIdentity == 0) {
        cout << "You currently have $" << money << "."<< endl;
        int bet = 0;
        while (bet < tableBuyIn || bet > money ) {
            cout <<  "How much money would you like to bet? (minimum bet is $" << tableBuyIn << ")";
            cin >> bet;
            if (bet <= 0) {
                cout << "Invalid input, bet must be a positive integer.\n\n";
            }
            else if(bet < tableBuyIn){
               cout << "Invalid input, table minimum bet is $" << tableBuyIn << "\n\n";
            }
            else if (bet > money) {
                cout << "Invalid input, insufficient funds.\n\n";
            }
        }
        return bet;
    }
    else if (playerIdentity == 6) {
        return 0;
    }
    else {
        return tableBuyIn;
    }
}


// puts the parameter Cards into the pile of Cards that the player remembers
// based on their playerIdentity
void Player::cardCount(Card * discard) {
    switch (playerIdentity) {
        case 2: // super card counter
                rememberedDiscards.push_back(discard);
            break;
        case 3: // regular card counter keeps a running tally
            // If the top card of the other player is b/w 2 and 6, add 1 to the running count
            if (discard->getNumericValue() >= 2 and discard->getNumericValue() <= 6) {
                discardTally++;
            }
            // If the top card of the other player is a Jack, Queen, King, or Ace, subtract one from the running count
            else if (discard->getNumericValue() == 1 or discard->getNumericValue() == 10) {
                discardTally--;
            }
            break;
        default:
            break;
    }
}

void Player::resetCounting() {
    rememberedDiscards.clear();
    discardTally = 0;
}


// removes the cards from the player's hand
// (at the end of the round)
void Player::clearHand() {
    hand.clear();
}