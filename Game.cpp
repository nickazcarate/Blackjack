// Created by Nick Azcarate on 4/15/18.
#include "Game.h"

Card * dealersTopCard;

Game::Game(int userGameTypeChoice){
    unusedCards = new DeckStack(6);
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
    getNumPlayers();
    getAmountMoney();

    for(int i = 0; i < numPlayers; i++){
        players.push_back(new Player(amountMoney, i)); //creates the number of other players desired
    }
    random_shuffle(players.begin(), players.end()); //shuffles the players to have random placement around the table
    //add dealer as the last person in the vector
    players.push_back(new Player(0, 6));

    userIndex = determineUserIndex(); //determine at which index in the player vector is the user to be used throughout the game
    int roundCounter = 0;
    // goes as long as the user has enough money for another round
    while (players.at(userIndex)->getMoney() > 15) { //should we change to table buy in??
        roundCounter++;
        cout << "\nStarting Round #" <<roundCounter << ":\n";
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

void Game::getNumPlayers() {
    cout << "\nHow many other players do you want in the game?\n";
    this_thread::sleep_for(chrono::milliseconds(600));
    cout << "Enter an integer from 0 to 5: ";
    while(true) {
        cin >> numPlayers;
        numPlayers++; //adding a player to account for the user running the game

        //Check for valid input
        //what happens when we have a decimal
        //
        if (numPlayers > 0 && numPlayers < 7) {
            return; //this is a valid input
        }
        cout << "\nInvalid input. Please enter an integer from 0 to 5: ";
        //clears the input stream to allow the user to input an acceptable value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    //FINISH do something about not allowing users to input decimals. even if they put 6.4, we dont want this to work.
//    if(numPlayers == 1){
//        cout << "You will be playing 1 on 1 against the dealer";
//    }
//    else{
//        cout << numPlayers - 1 << " other players in game entered.";
//    }
}

void Game::getAmountMoney() {
    bool moneyCheck = true;
    cout << "\nHow much money should each player start with?\n";
    this_thread::sleep_for(chrono::milliseconds(600));
    cout << "Enter an integer greater than or equal to $100: ";
    while (moneyCheck) {
        cin >> amountMoney;

        //Check for valid user input
        if (amountMoney >= 100) {
            return; //this is a valid input
        }
        else {
            cout << "\nInvalid input. Please enter an integer greater than or equal to $100: ";

            //clears the input stream to allow the user to input an acceptable value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
