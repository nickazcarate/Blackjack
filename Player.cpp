// Project created by Nick Azcarate, Colby Lathrop, Gregory DeCanio, Asher Johnson Hogan, Davis Washburn, Spencer Warren on 4/14/18.

#include "Player.h"


// Called in takeTurn() in Game.cpp
int Player::stand() {
    return 1;
}

// Called in Game.cpp
int Player::getCard() {
    return 2;
}

// Called in Game.cpp
int Player::doubleDown() {
    if (curBet * 2 > money) {
        return getCard();
    }
    return 3;
}

// may implement later
int Player::surrender() {
    return 4;
}

// Getter for player type (Specific bot strategy, dealer, or human player)
int Player::getPlayerIdentity(){
    return this->playerIdentity;
}

// Initialize the Player Object
Player::Player(int money, int playerIdentity) {

    this->money = money;
    this->playerIdentity = playerIdentity;
    gamesWon = 0;
    gamesLost = 0;
    gamesTied = 0;
    hasNatural = false;

}

// Getter for player's current money total
int Player::getMoney() {
    return this->money;
}

// Getter for the vector of cards that is the player's hand
vector<Card*> Player::getHand() {
    return this->hand;
}

// Increment number of games won
void Player::wonGame() {
    gamesWon++;
}

// Increment number of games lost
void Player::lostGame() {
    gamesLost++;
}

// Increment number of games tied with dealer
void Player::tiedGame() {
    gamesTied++;
}

// Getter for number of wins
int Player::getWins() {
    return gamesWon;
}

// Getter for number of losses
int Player::getLosses() {
    return gamesLost;
}

// Getter for number of ties
int Player::getTies() {
    return gamesTied;
}

// Getter for boolean whether or not the player has a natural 21
bool Player::getNatural() {
    return hasNatural;
}

// Setter for natural 21 boolean
void Player::setNatural(bool value) {
    hasNatural = value;
}

// Sets numDecks, called once by Game before the game starts
void Player::setNumDecks(int numDecks) {
    this->numDecks = numDecks;
}

// Check probability that a card of a specified value would be drawn
double Player::getProbability(int cardValue) {
    double probability = 0;
    int cardValCount = 0;

    // Call the getter for numberDecks within DeckStack
    int deckCount = numDecks;

    // Goes through the list of cards that are currently in play or have been in play since the last time the deck was shuffled.
    for (Card * card : rememberedDiscards) {

       // Grabs value of the card in the current space in rememberedDiscards
       int testValue = card->getNumericValue();

       // If the current card is the same as the requested value,
       // increment its count
       if (testValue == cardValue) {
            cardValCount++;
       }
    }

    if (cardValue == 10) {

        // probability = number of cards of specified value remaining divided by total cards that are left
        // 16 = number of Jacks, Queens, Kings, and 10s in one deck of cards
        probability = (double)((16*deckCount)-cardValCount)/(double)((deckCount*52)-rememberedDiscards.size());
    }
    else {

        //probability = number of cards of specified value remaining divided by total cards that are left
        probability = (double)((4*deckCount)-cardValCount)/(double)((deckCount*52)-rememberedDiscards.size()); //
    }

    return probability;
}

// Runs specific functions depending on the player type that runs the turns
int Player::takeTurn(Card * dealersTop) {
    switch (playerIdentity) {

        // Human Player
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
                if (temp == "1" or temp == "2") {
                    // Returns the user's choice so game can use it
                    return stoi(temp);
                }
                else if (temp == "3") {
                    if (curBet * 2 > money)
                        cout << "Invalid input, you don't have enough money to double down.\n";
                    else
                        return stoi(temp);
                }
                else if (temp == "4") {
                    if (hand.size() > 2)
                        cout << "Invalid input, you can only surrender at the beginning of your turn.\n";
                    else
                        return stoi(temp);
                }
                else {
                    cout << "Invalid input, please enter 1, 2, 3, or 4.\n";
                }
            }
        }

        // Various Bot strategies
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

        // Dealer
        case 6:
            return dealerTurn();
        default:
            return randoTurn();
    }
}

// Stops hitting at a hard 17. Will continue to hit if at a soft 17
int Player::dealerTurn(){
    if((getHandTotals().at(0) >= 17) or (getHandTotals().at(getHandTotals().size() - 1) >= 18)) {
        return stand();
    }
    else {
        return getCard();
    }
}

// Randomly chooses to get card, double down, or stand
int Player::randoTurn(){
    int randNum = rand()%100 +1;
    if (randNum <= 65) {                            // 65% chance the bot will hit
        return getCard();
    }
    else if((randNum > 65) && (randNum <= 70)) {    // 5% chance the bot will double down
        return doubleDown();
    }
    else                                            // 30% chance the bot will stand
        return stand();
}

// This person uses a card counting strategy, remembering ALL of the cards
int Player::superCardCounterTurn(Card * dealersTop) {

    // gets dealer's top card
    int topCard = dealersTop->getNumericValue();

    // Gets the hand value (If A can be 11 without total hand value being greater than 21, it is set to 11)
    int handValue = getBestHand();

    double bustChance = 0;
    double safeChance = 0;
    double riskValue = 0;
    double twentyOneChance = getProbability(21-handValue);

    //The bot plays riskier depending on the card the dealer shows. With Ace being the riskiest and
    if (topCard == 1) {
        riskValue = 6.0;
    }
    else if (topCard == 10) {
        riskValue = 5.5;
    }
    else {
        riskValue = 5;
    }

    //Check probability of That any card drawn will bust them and puts the value in the appropriate variable
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
    else if (bustChance < riskValue / 10.0) {
        return getCard();
    }
    else {
        return stand();
    }

}

// This person uses a card counting strategy, using the true count and run count to make betting decisions
// Uses "illustrious 18" strategy outlined here https://www.888casino.com/blog/blackjack-strategy-guide/blackjack-card-counting
int Player::weakCardCounterTurn(Card *dealersTop) {
    updateTrueCount();
    int topCard = dealersTop->getNumericValue();            // gets dealer's top card
    int handTotal = getHandTotals().at(0);                  // gets soft total for hand
    switch (handTotal)
    {
        case 16:                                            // if your hand is 16
            if ((topCard == 10) && (trueCount >= 0))         // the dealer's top card is 9, and the true count is +5 or above
                return stand();
            else if ((topCard == 9) && (trueCount >= 5))     // the dealer's top card is 10, Jack, Queen, or King, and the true count is 0 or above
                return stand();
            else
                return getCard();
        case 15:                                            // if your hand is 15
            if ((topCard == 10) && (trueCount >= 4))         // the dealer's top card is 10, Jack, Queen, or King, and the true count is +4 or above
                return stand();
            else getCard();
        case 13:                                            // if your hand is 13
            if ((topCard == 2) && (trueCount >= -1))         // the dealer's top card is 2, and the true count is -1 or above
                return stand();
            else if ((topCard == 3) && (trueCount >= -2))    // the dealer's top card is 3, and the true count is -2 or above
                return stand();
            else
                return getCard();
        case 12:                                            // if your hand is 12
            if ((topCard == 2) && (trueCount >= 4))
                return stand();
            else if ((topCard == 3) && (trueCount >= 2))     // the dealer's top card is 3, and the true count is +2 or above
                return stand();
            else if ((topCard == 4) && (trueCount >= 0))     // the dealer's top card is 4, and the true count is 0 or above
                return stand();
            else if (((topCard == 5) || (topCard == 6)) && (trueCount >= -1))         // the dealer's top card is a 5 or 6, and the true count is -1 or above
                return stand();
            else
                return getCard();
        case 11:                                            // if your hand is 11
            if ((topCard == 1) && (trueCount >= 1))          // the dealer's top card is an Ace, and the true count is +1 or above
                return doubleDown();
            else
                return getCard();
        case 10:                                            // if your hand is 10
            if ((topCard == 10) && (trueCount >= 4))         // the dealer's top card is 10, Jack, Queen, or King, and the true count is +4 or above
                return doubleDown();
            else if ((topCard == 1) && (trueCount >= 4))     // the dealer's top card is an Ace, and the true count is +4 or above
                return doubleDown();
            else
                return getCard();
        case 9:                                            // if your hand is 9
            if ((topCard == 2) && (trueCount >= 1))         // the dealer's top card is 2, and the true count is +1 or above
                return doubleDown();
            else if ((topCard == 7) && (trueCount >= 4))    // the dealer's top card is 7, and the true count is +4 or above
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
void Player::updateTrueCount()     // computes the true count by dividing the running count by the number of decks in play
{
    trueCount = (runningCount)/(numDecks * 52.0 - discardTally) * 52.0;
}

// This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
// strategy for hard totals
int Player::basicHardTurn(Card * dealersTop){
    int dealerTopCardNumVal = dealersTop->getNumericValue();        // returns the dealer's top card value
    int handTotal = getHandTotals().at(getHandTotals().size()-1);
    switch(handTotal){                                              // gives the current card total
        case 16:                                                    // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 15:                                                    // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 14:                                                    // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 13:                                                    // stand if dealer's upcard is 2-6, hit if 7-Ace
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 12:                                                    // stand if dealer's upcard is 4-6, hit if 2, 3, or 7-Ace
            if ((dealerTopCardNumVal >= 4) && (dealerTopCardNumVal <= 6))
                return stand();
            else
                return getCard();
        case 11:                                                    // always double down
            return doubleDown();
        case 10:                                                    // double down if dealer's upcard is 2-9, hit if 10, face, or Ace
            if ((dealerTopCardNumVal >= 2 && dealerTopCardNumVal <= 9))
                return doubleDown();
            else
                return getCard();
        case 9:                                                     // double down if dealer's upcard is 3-6, hit if 2, or 7-Ace
            if ((dealerTopCardNumVal >= 3 && dealerTopCardNumVal <= 6))
                return doubleDown();
            else
                return getCard();
        default:
            if (handTotal >= 17)                                    // if the hand total is 17 or higher
                return stand();                                     // stand
            else                                                    // if the hand total is 8 or lower
                return getCard();                                   // hit
    }
}

// This person uses https://www.blackjackapprenticeship.com/resources/blackjack-strategy-charts/
// strategy for soft totals
int Player::basicSoftTurn(Card * dealersTop){
    int dealerTopCardNumVal = dealersTop->getNumericValue();
    int handTotal = getHandTotals().at(0);
    switch(handTotal){                  // gives the current soft total
        case 19:                        // doubles against dealer's 6, otherwise stands
            if (dealerTopCardNumVal == 6)
                return doubleDown();
            else
                return stand();
        case 18:                        // doubles against dealer's 2 through 6, and hits against 9 through Ace, otherwise stands
            if ((dealerTopCardNumVal >= 2) && (dealerTopCardNumVal <= 6))
                return doubleDown();
            else if((dealerTopCardNumVal == 9) || (dealerTopCardNumVal == 10) || (dealerTopCardNumVal == 1))
                return getCard();
            else
                return stand();
        case 17:                        // doubles against dealer's 3 through 6, otherwise hits
            if ((dealerTopCardNumVal >= 3) && (dealerTopCardNumVal <= 6))
                return doubleDown();
            else
                return getCard();
        case 16:                        //doubles against dealer's 4 through 6, otherwise hits
            if ((dealerTopCardNumVal >= 4) && (dealerTopCardNumVal <= 6))
                return doubleDown();
            else
                return getCard();
        case 15:                        //doubles against dealer's 4 through 6, otherwise hits
            if ((dealerTopCardNumVal >= 4) && (dealerTopCardNumVal <= 6))
                return doubleDown();
            else
                return getCard();
        case 14:                        // doubles against dealer's 5 or 6, otherwise hits
            if ((dealerTopCardNumVal == 5) || (dealerTopCardNumVal == 6))
                return doubleDown();
            else
                return getCard();
        case 13:                        // doubles against dealer's 5 or 6, otherwise hits
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

// Update money to either taking away (negative parameter)
// or adding (positive parameter) money to the total
void Player::updateMoney(int difference){
    money += difference;
}

// Gives the user a card when dealt
void Player::giveCard(Card * card) {
    hand.push_back(card);
}

// Check and return the point value of a player's hand
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

    //if there is 1 or more aces, add 10 to the total
    if(hasAce){
        //note that in Blackjack, only 1 ace can be 11 (in a hand with multiple), the remainder are 1s
        totals.push_back(baseTotal + 10);
    }

    // removes totals that cause a bust (greater than 21)
    while (totals.size() > 1 && totals.at(totals.size() - 1) > 21) {
        totals.pop_back();
    }
    return totals;
}

// Get the value of the players hand (with Aces being 11 if the total remains under 21)
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
int Player::getBet(int tableBuyIn) {
    if(playerIdentity == 0) {
        cout << "You currently have $" << money << "."<< endl;
        int bet = 0;
        while (bet < tableBuyIn || bet > money ) {
            cout <<  "How much money would you like to bet? (minimum bet is $" << tableBuyIn << "): ";
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
        curBet = bet;
        return bet;
    }
    else if (playerIdentity == 6) {
        curBet = 0;
        return 0;
    }
    else {
        curBet = tableBuyIn;
        return tableBuyIn;
    }
}

// puts the parameter Cards into the pile of Cards that the player remembers
// based on their playerIdentity
// Halves method
void Player::cardCount(Card * discard) {
    switch (playerIdentity) {
        case 2: // super card counter
            rememberedDiscards.push_back(discard);
            break;

        case 3: // regular card counter keeps a running tally
            // If the top card of the other player is b/w 2 and 6, add 1 to the running count
            if (discard->getNumericValue() == 2 or discard->getNumericValue() == 7) {
                runningCount += .5;
            }
                // If the top card of the other player is a Jack, Queen, King, or Ace, subtract one from the running count
            else if (discard->getNumericValue() == 3 or discard->getNumericValue() == 4 or discard->getNumericValue() == 6) {
                runningCount += 1;
            }
            else if (discard->getNumericValue() == 5) {
                runningCount += 1.5;
            }
            else if (discard->getNumericValue() == 9) {
                runningCount -= .5;
            }
            else if (discard->getNumericValue() == 10 or discard->getNumericValue() == 1) {
                runningCount -= 1;
            }
            discardTally++;
            break;

        default:
            break;
    }
}

// Empties rememberedDiscards for the card counting bots when the decks are shuffled.
void Player::resetCounting() {
    rememberedDiscards.clear();
    runningCount = 0;
    discardTally = 0;
}

// removes the cards from the player's hand at the end of the round
void Player::clearHand() {
    hand.clear();
}

bool Player::canBet(int bet) {
    return (bet <= money);
}
