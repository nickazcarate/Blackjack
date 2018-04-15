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
    cout << "How many players would you like to play alongside with (not including dealer)?\n";
    cout << "Enter an integer from 0 (just you and the dealer) to 5: ";
    cin >> numPlayers;
    //getNumPlayers();
    //error handle
    cout << "\n\n How much money should each player start with?\n";
    cout << "Enter an integer greater than or equal to $100: ";
    //getAmtMoney();
    //error handle
    cin >> amtMoney;

    for(int i = 0; i < numPlayers; i++){
        players.push_back(new Player(amtMoney, true)); //creates the number of other players desired
    }
    players.push_back(new Player(amtMoney, false)); //creates the user
    random_shuffle(players.begin(), players.end()); //shuffles the players to have random placement around the table
}

void Game::runSimulationMode() {

}
