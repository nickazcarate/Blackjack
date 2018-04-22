// Project created by Nick Azcarate, Colby Lathrop, Gregory DeCanio, Asher Johnson Hogan, Davis Washburn, Spencer Warren on 4/14/18.

#include "Game.h"

Game::Game(int userGameTypeChoice){
    unusedPile = new DeckStack(6);
    discardPile = new DeckStack(0);

    if(userGameTypeChoice == 1){
        runPlayingMode();
    }
    else if(userGameTypeChoice == 2){
        runSimulationMode();
    }
}

int myRandom1(int i){
    return rand()%i;
}

int Game::determineUserIndex() {
    for(int i = 0; i < players.size(); i++){
        if(players[i]->getPlayerIdentity() == 0){ //if this player is the user, return the index
            return i;
        }
    }
    return -1;
}

void Game::runPlayingMode() {
    getNumPlayers();
    getAmountMoney();
    getMinBet();

    lastRoundShuffled = 0;

    for(int i = 0; i < numPlayers; i++){
        players.push_back(new Player(amountMoney, i)); //creates the number of other players desired
    }
    random_shuffle(players.begin(), players.end(), myRandom1); //shuffles the players to have random placement around the table
    //add dealer as the last person in the vector
    players.push_back(new Player(0, 6));

    // passes the number of decks in to each player
    // used by card counting bots
    for (Player * p : players) {
        p->setNumDecks(unusedPile->getNumDecks());
    }

    userIndex = determineUserIndex(); //determine at which index in the player vector is the user to be used throughout the game
    int roundCounter = 0;

    // stores the dealer
    Player * dealer = players.at(players.size() - 1);

    // goes as long as the user has enough money for another round
    while (players.at(userIndex)->getMoney() >= tableBuyIn) {
        roundCounter++;
        cout << "\nStarting Round #" <<roundCounter << ":\n";
        //stores player's bets
        vector<int> bets;
        vector<bool> surrendered(numPlayers);

        // deals two cards to every player
        for (Player* p : players) {
            p->giveCard(unusedPile->getTopCard());// places card in user's hand and then deletes it from unusedPile
            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
            p->giveCard(unusedPile->getTopCard());
            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
        }
        bool dealerHasNatural = false;
        // checks if the dealer has a natural, if he does, boolean is tripped no one plays the round
        if (dealer->getBestHand() == 21)
        {
            dealerHasNatural = true;
        }
        // each player takes turn
        for (int i = 0; i < players.size(); i++) {
            Player * p = players.at(i);
            // adds p's bet to bets
            bets.push_back(p->getBet(tableBuyIn));
            if(p->getPlayerIdentity() == 0) {
                cout << "The dealer's top card is: " << dealer->getHand().at(0)->getValue();
            }
            bool endTurn = false;
            p->setNatural(false);                       // sets that the player does not have a natural at the beginning of the turn
            if (p->getBestHand() == 21)                 // if you start with 21
            {
                endTurn = true;                         // your turn automatically ends
                p->setNatural(true);                    // mark they have a natural
                if (p->getPlayerIdentity() == 0)        // if you are the human player
                {
                    cout << "\nYour current hand is: ";
                    for (Card *c : p->getHand()) {
                        cout << c->getValue() << " ";
                    }
                    cout << "\nYou have 21!\n";
                }
            }
            // prints your cards if the dealer has a natural and you do not
            if ((p->getBestHand() != 21) and (dealerHasNatural))       // if dealer has natural and you do not
            {
                if (p->getPlayerIdentity() == 0)        // if you are the human player
                {
                    cout << "\nYour current hand is: ";
                    for (Card *c : p->getHand()) {
                        cout << c->getValue() << " ";
                    }
                }
            }
            while (!endTurn and !dealerHasNatural) {
                // if their hand total is over 21, end turn
                if (p->getHandTotals().at(0) > 21) {
                    //getHandTotals().at(0) is the baseTotal, which is the lowest possible total
                    //if this total is already > 21, then the player busts (is out of the round)
                    if(p->getPlayerIdentity() == 0) {
                        cout << "\nYour current hand is: ";
                        for (Card *c : p->getHand()) {
                            cout << " " << c->getValue();
                        }
                        cout << "\t\tYou bust! :(\n";
                    }
                    endTurn = true;
                }
                else if (p->getBestHand() == 21) {
                    if(p->getPlayerIdentity() == 0) {
                        cout << "\nYour current hand is: ";
                        for (Card *c : p->getHand()) {
                            cout << " " << c->getValue();
                        }
                    }
                    cout << "\n";
                    endTurn = true;
                }

                else {
                    // gets player action (passes in dealer's top card so user can see it)
                    int playerAction = p->takeTurn(players.at(players.size() - 1)->getHand().at(0));
                    switch (playerAction) {
                        case 1: // stand
                            endTurn = true;
                            break;
                        case 2: // hit
                            p->giveCard(unusedPile->getTopCard()); //places card into player's hand and then deletes the card
                            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
                            break;
                        case 3: // double down
                            p->giveCard(unusedPile->getTopCard()); //places card into player's hand and then deletes the card
                            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
                            bets.at(i) = bets.at(i) * 2;
                            if(p->getPlayerIdentity() == 0) {
                                cout << "\nYour current hand is: ";
                                for (Card *c : p->getHand()) {
                                    cout << c->getValue() << " ";
                                }
                                cout << endl;
                                if (p->getBestHand() > 21) {
                                    cout <<"\nYou bust! :(";
                                }
                            }
                            endTurn = true;
                            break;
                        case 4: // surrender
                            bets.at(i) = bets.at(i) / 2;
                            surrendered.at(i) = true;
                            endTurn = true;
                            break;
                    }
                }
            }
        }

        cout << "\nThe dealer's hand is: ";
        for (Card *c : dealer->getHand()) {
            cout << c->getValue() << " ";
        }
        cout << endl;

        // runs through each player and compares their hand to the dealer
        for (int i = 0; i < players.size() - 1; i++) {
            Player * player = players.at(i);
            // if the player busts, remove their bet from their money
            // and give it to the dealer
            if (player->getBestHand() > 21 or surrendered.at(i)) {
                player->updateMoney(bets.at(i) * -1);
                dealer->updateMoney(bets.at(i));
                player->lostGame();
            }
                // else if the dealer got a natural
            else if (dealerHasNatural) {
                // if the player also got a natural, it's a tie
                // the player does not lose money, nor the dealer gets money
                if (player->getNatural())
                {
                    player->tiedGame();
                    if (player->getPlayerIdentity() == 0) {
                        cout << "\nYou and the dealer both have naturals. You tie!\n";
                    }
                }
                    // if the player did not get a natural, they lose
                    // the player loses his bet
                    // the dealer gets the player's bet
                else
                {
                    player->updateMoney(bets.at(i) * -1);
                    dealer->updateMoney(bets.at(i));
                    player->lostGame();
                    if (player->getPlayerIdentity() == 0) {
                        cout << "\nThe dealer has a natural and you don't. You lose!\n";
                    }
                }
            }
                // else if the player got a natural, and the dealer didn't
                // the player gets 1.5x their original bet
                // the dealer loses 1.5x the player's bet
            else if (player->getNatural()  and !(dealerHasNatural))
            {
                player->updateMoney((bets.at(i) * 3)/2);
                dealer->updateMoney((bets.at(i) * -3)/2);
                player->wonGame();
                if(player->getPlayerIdentity()== 0) {
                    cout << "\nYou got a natural and the dealer didn't. You win!\n";
                }
            }
                // else if the dealer busts or player beats them,
                // the player gets their bet back matched
                // and the dealer loses that much
            else if (dealer->getBestHand() > 21 or player->getBestHand() > dealer->getBestHand()) {
                player->updateMoney(bets.at(i));
                dealer->updateMoney(bets.at(i) * -1);
                player->wonGame();
                if (dealer->getBestHand() > 21 and player->getPlayerIdentity() == 0) {
                    cout << "\nDealer busts. You win!\n";
                } else if (player->getBestHand() > dealer->getBestHand() and player->getPlayerIdentity() == 0) {
                    cout << "\nYour hand is better than the dealer's. You win!\n";
                }
            }
                // else if the dealer wins, settle bets
            else if (dealer->getBestHand() > player->getBestHand()) {
                player->updateMoney(bets.at(i) * -1);
                dealer->updateMoney(bets.at(i));
                player->lostGame();
                if (player->getPlayerIdentity() == 0) {
                    cout << "\nThe dealer's hand is better yours. You lose!\n";
                }
            }
            // else, its a stand and nothing happens with the bets
            else {
                player->tiedGame();
                if(player->getPlayerIdentity() == 0){
                    cout <<"\nYou and the dealer had the same hand. It's a tie!\n";
                }
            }
        }

        // clears players' hands
        for (Player * p : players) {
            p->clearHand();
        }

        while (true) {
            cout << "\nWould you like to keep playing? (0 for no, 1 for yes) ";
            string keepPlaying;
            cin >> keepPlaying;

            if (keepPlaying == "0") {
                for (int i = 0; i < numPlayers; i++) {
                    Player * p = findPlayer(i);
                    cout << "Player " << p->getPlayerIdentity() << ":\n";
                    cout << "Total money: " << p->getMoney();
                    cout << "\nWon games: " << p->getWins();
                    cout << "\nLost games: " << p->getLosses();
                    cout << "\nTied games: " << p->getTies();
                    if (p->getLosses() != 0 || p->getWins() != 0) // prevents divide by zero error
                        cout << "\nWin percent: " << p->getWins() * 100 / (p->getLosses() + p->getWins()) << "%";
                    cout << "\nTotal rounds: " << p->getWins() + p->getLosses() + p->getTies() << endl;
                }
                return;
            }
            else if (keepPlaying == "1") {
                if (players.at(userIndex)->getMoney() <= tableBuyIn)
                {
                    cout << "\nToo bad, you ran out of money! :(\n";
                }
                break;
            }
            else {
                cout << "Invalid input, please enter 0 or 1\n";
            }
        }

        if (roundCounter - lastRoundShuffled > 6) {
            unusedPile = new DeckStack(6);
            discardPile = new DeckStack(0);
            lastRoundShuffled = roundCounter;
        }
    }
    for (int i = 0; i < numPlayers; i++) {
        Player * p = findPlayer(i);
        cout << "Player " << p->getPlayerIdentity() << ":\n";
        cout << "Total money: " << p->getMoney();
        cout << "\nWon games: " << p->getWins();
        cout << "\nLost games: " << p->getLosses();
        cout << "\nTied games: " << p->getTies();
        if (p->getLosses() != 0 || p->getWins() != 0) // prevents divide by zero error
            cout << "\nWin percent: " << p->getWins() * 100 / (p->getLosses() + p->getWins()) << "%";
        cout << "\nTotal rounds: " << p->getWins() + p->getLosses() + p->getTies() << endl;
    }
}

void Game::runSimulationMode() {
    getNumPlayers();
    getAmountMoney();
    getMinBet();

    lastRoundShuffled = 0;

    for(int i = 1; i < numPlayers; i++){
        players.push_back(new Player(amountMoney, i)); //creates the number of other players desired
    }
    random_shuffle(players.begin(), players.end(), myRandom1); //shuffles the players to have random placement around the table
    //add dealer as the last person in the vector
    players.push_back(new Player(0, 6));

    // passes the number of decks in to each player
    // used by card counting bots
    for (Player * p : players) {
        p->setNumDecks(unusedPile->getNumDecks());
    }

    int roundCounter = 0;
    // goes as long as the user has enough money for another round
    while (doPeopleHaveMoney() and roundCounter < 10000) {

        for (int i = 0; i < players.size() - 1; i++) {
            if (players.at(i)->getMoney() < tableBuyIn) {
                outPlayers.push_back(players.at(i));
                players.erase(players.begin() + i);
            }
        }

        roundCounter++;
        //stores player's bets
        vector<int> bets;
        vector<bool> surrendered(numPlayers);



        // deals two cards to every player
        for (Player* p : players) {
            p->giveCard(unusedPile->getTopCard());// places card in user's hand and then deletes it from unusedPile
            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
            p->giveCard(unusedPile->getTopCard());
            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
        }

        // each player takes turn
        for (int i = 0; i < players.size(); i++) {
            Player * p = players.at(i);
            // adds p's bet to bets
            bets.push_back(p->getBet(tableBuyIn));

            bool endTurn = false;

            while (!endTurn) {
                // if their hand total is over 21, end turn
                if (p->getHandTotals().at(0) > 21) {
                    //getHandTotals().at(0) is the baseTotal, which is the lowest possible total
                    //if this total is already > 21, then the player busts (is out of the round)
                    endTurn = true;
                }
                else if (p->getBestHand() == 21) {
                    endTurn = true;
                }

                else {
                    // gets player action (passes in dealer's top card so user can see it)
                    int playerAction = p->takeTurn(players.at(players.size() - 1)->getHand().at(0));
                    switch (playerAction) {
                        case 1: // stand
                            endTurn = true;
                            break;
                        case 2: // hit
                            p->giveCard(unusedPile->getTopCard()); //places card into player's hand and then deletes the card
                            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
                            break;
                        case 3: // double down
                            p->giveCard(unusedPile->getTopCard()); //places card into player's hand and then deletes the card
                            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
                            bets.at(i) = bets.at(i) * 2;
                            endTurn = true;
                            break;
                        case 4: // surrender
                            bets.at(i) = bets.at(i) / 2;
                            surrendered.at(i) = true;
                            endTurn = true;
                            break;
                    }
                }
            }
        }

        // stores the dealer
        Player * dealer = players.at(players.size() - 1);

        // runs through each player and compares their hand to the dealer
        for (int i = 0; i < players.size() - 1; i++) {
            Player * player = players.at(i);
            // if the player busts, remove their bet from their money
            // and give it to the dealer
            if (player->getBestHand() > 21 or surrendered.at(i)) {
                player->updateMoney(bets.at(i) * -1);
                dealer->updateMoney(bets.at(i));
                player->lostGame();
            }
                // else if the dealer busts or player beats them,
                // the player gets their bet back matched
                // and the dealer loses that much
            else if (dealer->getBestHand() > 21 or player->getBestHand() > dealer->getBestHand()) {
                player->updateMoney(bets.at(i));
                dealer->updateMoney(bets.at(i) * -1);
                player->wonGame();
            }
                // else if the dealer wins, settle bets
            else if (dealer->getBestHand() > player->getBestHand()) {
                player->updateMoney(bets.at(i) * -1);
                dealer->updateMoney(bets.at(i));
                player->lostGame();
            }
                // else, its a stand and nothing happens with the bets
            else {
                player->tiedGame();
            }
        }

        // clears players' hands
        for (Player * p : players) {
            p->clearHand();
        }

        //if (roundCounter - lastRoundShuffled > 6) {
        if (unusedPile->getCardStack().size() < 52) {
            unusedPile = new DeckStack(6);
            discardPile = new DeckStack(0);
            lastRoundShuffled = roundCounter;
            for (Player * p : players) {
                p->resetCounting();
            }
        }

        if (roundCounter == 500) {

        }

    }

    for (int i = 1; i < numPlayers; i++) {
        Player * p = findPlayer(i);
        cout << "\nPlayer " << p->getPlayerIdentity() << ":";
        cout << "\nTotal money: " << p->getMoney();
        cout << "\nWon games: " << p->getWins();
        cout << "\nLost games: " << p->getLosses();
        cout << "\nTied games: " << p->getTies();
        if (p->getLosses() != 0 || p->getWins() != 0) // prevents divide by zero error
            cout << "\nWin percent: " << p->getWins() * 100 / (p->getLosses() + p->getWins()) << "%";
        cout << "\nTotal rounds: " << p->getWins() + p->getLosses() + p->getTies() << endl;
    }

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
    cout << "\nHow much money should each player start with?\n";
    cout << "Enter an integer greater than or equal to $100: ";
    while (true) {
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

void Game::getMinBet() {
    cout << "\nHow much should the minimum bet be?\n";
    cout << "Enter an integer between $2 and $500 (and below player's starting money): ";
    while (true) {                  // while statement that error handles, printing the specific error
        cin >> tableBuyIn;
        //Check for valid user input
        if ((tableBuyIn >= 2) && (tableBuyIn <= 500) && (tableBuyIn < amountMoney)) {
            return; //this is a valid input
        }
        else {                                  // if input is not valid, generally says "invalid input"
            cout << "\nInvalid input, enter an integer between $2 and $500 (and below player's starting money): ";
            //clears the input stream to allow the user to input an acceptable value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (tableBuyIn < amountMoney)       // prints error that input is above player's starting money
            {
                cout << " Please make sure the integer is below player's starting money.\n";
            }
            if ((tableBuyIn <= 2) && (tableBuyIn >= 500))       // prints error that input is not b/w $2 and $500
            {
                cout << " Please make sure the integer is between $2 and $500.\n";
            }
        }
    }
}

void Game::discard(Card * card) {
    for (Player * p : players) {
        p->cardCount(card);
    }
    discardPile->addCard(card);
}

bool Game::doPeopleHaveMoney() {
    for (int i = 0; i < players.size() - 1; i++) {
        if (players.at(i)->getMoney() >= tableBuyIn)
            return true;
    }
    return false;
}

Player * Game::findPlayer(int playerIdentity) {
    for (Player * p : players) {
        if (p->getPlayerIdentity() == playerIdentity) {
            return p;
        }
    }
    for (Player * p : outPlayers) {
        if (p->getPlayerIdentity() == playerIdentity) {
            return p;
        }
    }
    return NULL;
}
