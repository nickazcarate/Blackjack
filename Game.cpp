// Created by Nick Azcarate on 4/15/18.
#include "Game.h"

Card * dealersTopCard;

Game::Game(int userGameTypeChoice, int tableBuyIn){
    unusedCards = new DeckStack(6);
    this->tableBuyIn = tableBuyIn;
    if(userGameTypeChoice == 1){
        runPlayingMode();
    }
    else if(userGameTypeChoice == 2){
        runSimulationMode();
    }
    else{
        //error handle
    }
}

int Game::determineUserIndex() {
    for(int i = 0; i < players.size(); i++){
        if(players[i]->getPlayerIdentity() == 0){ //if this player is the user, return the index
            return i;
        }
    }
}

void Game::runPlayingMode() {
    numPlayers = getNumPlayers();
    amountMoney = getAmountMoney();

    for(int i = 0; i < numPlayers; i++){
        players.push_back(new Player(amountMoney, i)); //creates the number of other players desired
    }
    random_shuffle(players.begin(), players.end()); //shuffles the players to have random placement around the table
    //add dealer as the last person in the vector
    players.push_back(new Player(0, 6));

    userIndex = determineUserIndex(); //determine at which index in the player vector is the user to be used throughout the game

    // goes as long as the user has enough money for another round
    while (players.at(userIndex)->getMoney() > tableBuyIn) {

        //stores player's bets
        vector<int> bets;

        // deals two cards to every player
        for (Player* p : players) {

            p->giveCard(unusedCards->removeTopCard());//FINISH! put these in the discard pile before removing

            p->giveCard(unusedCards->removeTopCard());
        }

        // each player takes turn
        for (Player * p : players) {
            // adds p's bet to bets
            bets.push_back(p->getBet());

            bool endTurn = false;
            while (!endTurn) {
                // if their hand total is over 21, end turn
                if (p->getHandTotals().at(0) > 21) {
                    //getHandTotals().at(0) is the baseTotal, which is the lowest possible total
                    //if this total is already > 21, then the player busts (is out of the round)
                    endTurn = true;
                }
                else if (p->getBestHand() == 21) {
                    cout << "You have 21!\n";
                    endTurn = true;
                }

                else {
                    // gets player action (passes in dealer's top card so user can see it)
                    int playerAction = p->takeTurn(players.at(players.size() - 1)->getHand().at(0));
                    switch (playerAction) {
                        case 0: // stand
                            endTurn = true;
                            break;
                        case 1: // hit
                            p->giveCard(unusedCards->removeTopCard());
                    }
                }
            }
        }

    }
}

void Game::runSimulationMode() {

}

void Game::gamePlay() {
    while(true){
        //if();
        //game runs if at least one person has money

    }
}

vector<Player *> Game::getPlayers(){
    return this->players;
}

int Game::getTableBuyIn(){
    return this->tableBuyIn;
}

int Game::getNumPlayers() {
    cout << "How many players do you want in the game?\n";
    cout << "Enter an integer from 1 to 6: ";
    while(true) {
        cin >> numPlayers;

        //Check for valid input
        //what happens when we have a decimal
        //
        if (numPlayers > 0 && numPlayers < 7) {
            return numPlayers;
        }
        cout << "\nInvalid input. Please enter an integer from 1-6: ";
        //clears the input stream to allow the user to input an acceptable value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int Game::getAmountMoney() {
    bool moneyCheck = true;

    cout << "\n\nHow much money should each player start with?\n";
    cout << "Enter an integer greater than or equal to $100: ";
    int moneyVal;
    while (moneyCheck) {
        cin >> moneyVal;

        //Check for valid user input
        if (moneyVal >= 100) {
            return moneyVal;
        }
        else {
            cout << "\nInvalid input. Please enter an integer greater than or equal to $100: ";

            //clears the input stream to allow the user to input an acceptable value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
