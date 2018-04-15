// Created by Nick Azcarate on 4/15/18.
#include "Game.h"

Game::Game(int userGameTypeChoice, int tableBuyIn){
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

int Game::getNumPlayers() {
    bool playerCheck = true;
    while(playerCheck) {

        cout << "How many players do you want in the game?\n";
        cout << "Enter an integer from 1 to 6: ";
        cin >> numPlayers;

        //Check for valid input
        //what happens when we have a decimal
        if (numPlayers > 0 && numPlayers < 7) {
            playerCheck = false;
            return numPlayers;
        }
        else {
            cout << "\nInvalid value. Please enter an integer from 1-6: ";
            //clears the input stream to allow the user to input an acceptable value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
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
            cout << "\nInvalid Input. Please enter an integer greater than or equal to $100: ";

            //clears the input stream to allow the user to input an acceptable value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

vector<Player *> Game::getPlayers(){
    return this->players;
}

void Game::gamePlay() {
    while(true){
        //if();
        //game runs if at least one person has money

    }
}

int Game::getTableBuyIn(){
    return this->tableBuyIn;
}

void Game::runPlayingMode() {

    numPlayers = getNumPlayers();
    amountMoney = getAmountMoney();

    for(int i = 0; i < numPlayers; i++){
        players.push_back(new Player(amountMoney, true)); //creates the number of other players desired
    }
    players.push_back(new Player(amountMoney, false)); //creates the user
    random_shuffle(players.begin(), players.end()); //shuffles the players to have random placement around the table
    //add dealer as the last person always
}

void Game::runSimulationMode() {

}
