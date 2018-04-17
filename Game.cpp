// Created by Nick Azcarate on 4/15/18.
#include "Game.h"

Card * dealersTopCard;

Game::Game(int userGameTypeChoice, int tableBuyIn){
    deck = new DeckStack(6);
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

void Game::runPlayingMode() {
    numPlayers = getNumPlayers();
    amountMoney = getAmountMoney();

    players.push_back(new Player(amountMoney, 0)); //creates the user
    for(int i = 0; i < numPlayers; i++){
        players.push_back(new Player(amountMoney, 2)); //creates the number of other players desired
    }
    random_shuffle(players.begin() + 1, players.end()); //shuffles the players other than the user to have random placement around the table
    //add dealer as the last person always
    players.push_back(new Player(0, 1));

    // goes as long as the user has money
    while (players.at(0)->getMoney() > 0) {
        for (Player* p : players) {
            p->giveCard(deck->removeTopCard());
            p->giveCard(deck->removeTopCard());
        }
        for (Player* p : players) {
            bool endTurn = false;
            while (!endTurn) {
                int playerAction = p->takeTurn(players.at(players.size() - 1)->getHand().at(0));
                switch (playerAction) {
                    case 0:
                        endTurn = true;
                        break;
                    case 1:
                        p->giveCard(deck->removeTopCard());
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
  return 0;
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
