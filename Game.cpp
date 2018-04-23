/*
 * Game.cpp
 *
 * by Nicolas Azcarate, Gregory DeCanio, Asher Johnson Hogan,
 * Colby Lathrop, Spencer Warren, and Davis Washburn
 */

#include "Game.h"

Game::Game(int userGameTypeChoice){
    getNumPlayers(userGameTypeChoice);
    getAmountMoney();
    getMinBet();
    unusedPile = new DeckStack(6);
    discardPile = new DeckStack(0);
    bets = *(new vector<int> (numPlayers));
    surrendered = *(new vector <bool> (numPlayers));

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

void Game::stand(Player * p){
    p->setEndTurn(true);
}

void Game::hit(Player * p){
    p->giveCard(unusedPile->getTopCard()); //places card into player's hand and then deletes the card
    discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
}

void Game::doubleDown(Player * p) {
    int seat = findPlayerSeat(p);
    p->giveCard(unusedPile->getTopCard()); //places card into player's hand and then deletes the card
    discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
    bets.at(seat) = bets.at(seat) * 2;
    p->setEndTurn(true);
}

void Game::surrender(Player * p) {
    // surrender
    int seat = findPlayerSeat(p);
    bets.at(seat) = bets.at(seat) / 2;
    surrendered.at(seat) = true;
    p->setEndTurn(true);
}

int Game::findPlayerSeat(Player * p) {
    for(int i = 0; i < players.size(); i++){
        if(players[i]->getPlayerIdentity() == p->getPlayerIdentity()){ //if this player is the one we're looking for, return the index of their seat
            return i;
        }
    }
    return -1;
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
    lastRoundShuffled = 0;
    vector<string> names = {"You", "RandomBot", "SuperCounterBot", "ModerateCounterBot", "BasicStrategyBot1", "BasicStrategyBot2"};
    for(int i = 0; i < numPlayers; i++){
        players.push_back(new Player(amountMoney, i, names[i])); //creates the number of other players desired
    }
    random_shuffle(players.begin(), players.end(), myRandom1); //shuffles the players to have random placement around the table

    //add dealer as the last person in the vector
    players.push_back(new Player(0, 6, "Dealer"));

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
        bets = *(new vector<int> (numPlayers));
        surrendered = *(new vector <bool> (numPlayers));

        cout << "\nStarting Round #" <<roundCounter << ":\n\n";

        // deals two cards to every player
        for (Player* p : players) {
            p->giveCard(unusedPile->getTopCard()); // places card in user's hand and then deletes it from unusedPile
            discard(unusedPile->removeTopCard());  // places card in discardPile cardStack
            p->giveCard(unusedPile->getTopCard());
            discard(unusedPile->removeTopCard());  // places card in discardPile cardStack
        }

        // checks if the dealer has a natural, if he does, boolean is tripped no one plays the round
        bool dealerHasNatural = dealer->getBestHand() == 21;

        // adds p's bet to bets
        for (int i = 0; i < players.size() - 1; i++) {
            bets.at(i) = players.at(i)->getBet(tableBuyIn);
        }

        cout << "The dealer shows: \n";
        dealer->printTop();
        this_thread::sleep_for(chrono::milliseconds(sleepTime));

        // each player takes turn
        for (int i = 0; i < players.size(); i++) {

            cout << "\n************************************************************************************************\n";

            Player * p = players.at(i);
            string name = p->getPlayerName();

            if (i == userIndex) {
                cout << "\nIt's your turn!\n";
            }
            else {
                cout << "\nIt's " << name << "'s turn.\n";
            }
            this_thread::sleep_for(chrono::milliseconds(sleepTime));

            p->setEndTurn(false);
            p->setNatural(false);                       // sets that the player does not have a natural at the beginning of the turn
            if (p->getBestHand() == 21) {
                p->setEndTurn(true);                         // your turn automatically ends
                p->setNatural(true);                    // mark they have a natural
                if (i == userIndex)        // if you are the human player
                {
                    cout << "\nYour current hand is: \n";
                    p->printHand();
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    cout << "\nYou have 21!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
                else  { // for the bots and the dealer
                    cout << "\n" << name << "'s current hand is: \n";
                    p->printHand();
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    cout << "\n" << name << " has 21!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
            }

            // prints your cards if the dealer has a natural and you do not
            if ((p->getBestHand() != 21) and (dealerHasNatural))       // if dealer has natural and you do not
            {
                if (p->getPlayerIdentity() == 0)        // if you are the human player
                {
                    cout << "\nYour current hand is: \n";
                    p->printHand();
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    cout << "\t Hand total: " << p->getBestHand();
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
                else if (i != players.size() - 1) { // for the bots, not the dealer
                    cout << name << "'s current hand is: \n";
                    p->printHand();
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    cout << "\t Hand total: " << p->getBestHand();
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }

            }
            while (!p->getEndTurn() and !dealerHasNatural) {
                // if their hand total is over 21, end turn
                if (p->getHandTotals().at(0) > 21) {
                    //getHandTotals().at(0) is the baseTotal, which is the lowest possible total
                    //if this total is already > 21, then the player busts (is out of the round)
                    if(p->getPlayerIdentity() == 0) {
                        cout << "\nYour current hand is: \n";
                        p->printHand();
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                        cout << "\t Hand total: " << p->getBestHand() << endl;
                        cout << "\nYou bust! :(\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }
                    else if (i != players.size() - 1) { // for the bots, not the dealer
                        cout << "\n" << name << "'s current hand is: \n";
                        p->printHand();
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                        cout << "\t Hand total: " << p->getBestHand();
                        cout << "\n" << name << " busts!\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }
                    p->setEndTurn(true);
                }
                else if (p->getBestHand() == 21) {
                    if(p->getPlayerIdentity() == 0) {
                        cout << "\nYour current hand is: \n";
                        p->printHand();
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                        cout << "\tYou got 21!\n";
                    }
                    else if (i != players.size() - 1) { // for the bots, not the dealer
                        cout << "\n" << name << "'s current hand is: \n";
                        p->printHand();
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                        cout << "\t" << name << " got 21!\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }
                    p->setEndTurn(true);
                }

                else {
                    // gets player action (passes in dealer's top card so user can see it)
                    int playerAction = p->takeTurn(players.at(players.size() - 1)->getHand().at(0));

                    if (i != userIndex) { // for the bots and the dealer
                        cout << "\n" << name << "'s current hand is: \n";
                        p->printHand();
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                        cout << "\t Hand total: " << p->getBestHand();
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }

                    switch (playerAction) {
                        case 1: // stand
                            stand(p);
                            if (i != userIndex) { // for the bots and the dealer
                                cout << "\n" << name << " is standing.\n";
                                this_thread::sleep_for(chrono::milliseconds(sleepTime));
                            }
                            break;
                        case 2: // hit
                            hit(p);
                            if (i != userIndex) { // for the bots and the dealer
                                cout << "\n" << name << " is hitting.\n";
                                this_thread::sleep_for(chrono::milliseconds(sleepTime));
                            }
                            break;
                        case 3: // double down
                            doubleDown(p);
                            if(p->getPlayerIdentity() == 0) {
                                cout << "\nYour hand is: \n";
                                p->printHand();
                                this_thread::sleep_for(chrono::milliseconds(sleepTime));
                                cout << "\t Hand total: " << p->getBestHand() << endl;
                                if (p->getBestHand() > 21) {
                                    cout << "You bust! :(";
                                }
                                this_thread::sleep_for(chrono::milliseconds(sleepTime));
                            }
                            else { // for the bots, not the dealer
                                cout << "\n" << name << " is doubling down.\n";
                                this_thread::sleep_for(chrono::milliseconds(sleepTime));
                                cout << "\n" << name << "'s hand is: \n";
                                p->printHand();
                                this_thread::sleep_for(chrono::milliseconds(sleepTime));
                                cout << "\t Hand total: " << p->getBestHand() << endl;
                                if (p->getBestHand() > 21) {
                                    cout << "\n" << name << " busts!";
                                }
                                this_thread::sleep_for(chrono::milliseconds(sleepTime));
                            }
                            break;
                        case 4: // surrender
                            surrender(p);
                            cout << "You surrendered.\n";
                            break;
                    }
                }
            }
        }

        cout << "\n************************************************************************************************\n";

        cout << "\nThe dealer's hand is: ";
        for (Card * card : dealer->getHand()) {
            cout << card->getValue() << " ";
        }
        cout << "\t Hand total: " << dealer->getBestHand() << "\n";
        this_thread::sleep_for(chrono::milliseconds(sleepTime));

        // runs through each player and compares their hand to the dealer
        for (int i = 0; i < players.size() - 1; i++) {

            Player * player = players.at(i);
            string name = player->getPlayerName();

            if(player->getPlayerIdentity() == 0) {
                cout << "\nYour hand is: ";
                for (Card * card : player->getHand()) {
                    cout << card->getValue() << " ";
                }
                cout << "\t Hand total: " << player->getBestHand();
            }
            else if (i != players.size() - 1) { // for the bots, not the dealer
                cout << "\n" << name << "'s hand is: ";
                for (Card * card : player->getHand()) {
                    cout << card->getValue() << " ";
                }
                cout << "\t Hand total: " << player->getBestHand();
            }

            // if the player busts, remove their bet from their money
            // and give it to the dealer
            if (player->getBestHand() > 21 || surrendered.at(i)) {

                if (player->getPlayerIdentity() == 0 and surrendered.at(i)) {
                    cout << "\nYou surrendered. You lose $" << bets.at(i) << "!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
                else if (player->getPlayerIdentity() == 0){
                    cout << "\nYou busted. You lose $" << bets.at(i) << "!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
                else if (i != players.size() - 1) { // for the bots, not the dealer
                    cout << "\n" << name << " busted. They lose $" << bets.at(i) << "!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }

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
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }
                    else if (i != players.size() - 1) { // for the bots, not the dealer
                        cout << "\n" << name << " and the dealer both have naturals. They tie!\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
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
                        cout << "\nThe dealer has a natural and you don't. You lose $" << bets.at(i) << "!\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }
                    else if (i != players.size() - 1) { // for the bots, not the dealer
                        cout << "\nThe dealer has a natural and " << name << " doesn't. They lose $" << bets.at(i) << "!\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
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
                    cout << "\nYou got a natural and the dealer didn't. You win $" << bets.at(i) << "!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
                else if (i != players.size() - 1) { // for the bots, not the dealer
                    cout << "\n" << name << " got a natural and the dealer didn't. They win $" << bets.at(i) << "!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
            }
                // else if the dealer busts or player beats them,
                // the player gets their bet back matched
                // and the dealer loses that much
            else if (dealer->getBestHand() > 21 or player->getBestHand() > dealer->getBestHand()) {
                player->updateMoney(bets.at(i));
                dealer->updateMoney(bets.at(i) * -1);
                player->wonGame();
                if (player->getPlayerIdentity() == 0) {
                    if (dealer->getBestHand() > 21) {
                        cout << "\nDealer busts. You win $" << bets.at(i) << "!\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }
                    else if (player->getBestHand() > dealer->getBestHand()) {
                        cout << "\nYour hand is better than the dealer's. You win $" << bets.at(i) << "!\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }
                }
                else if (i != players.size() - 1) { // for the bots, not the dealer
                    if (dealer->getBestHand() > 21) {
                        cout << "\nDealer busts. " << name << " wins $" << bets.at(i) << "!\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }
                    else if (player->getBestHand() > dealer->getBestHand()) {
                        cout << "\n" << name << "'s hand is better than the dealer's. They win $" << bets.at(i) << "!\n";
                        this_thread::sleep_for(chrono::milliseconds(sleepTime));
                    }
                }
            }
            // else if the dealer wins, settle bets
            else if (dealer->getBestHand() > player->getBestHand()) {
                player->updateMoney(bets.at(i) * -1);
                dealer->updateMoney(bets.at(i));
                player->lostGame();
                if (player->getPlayerIdentity() == 0) {
                    cout << "\nThe dealer's hand is better yours. You lose $" << bets.at(i) << "!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
                else if (i != players.size() - 1) { // for the bots, not the dealer
                    cout << "\nThe dealer's hand is better " << name << "'s. They lose $" << bets.at(i) << "!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }

            }
            // else, its a stand and nothing happens with the bets
            else {
                player->tiedGame();
                if(player->getPlayerIdentity() == 0){
                    cout <<"\nYou and the dealer had the same hand. It's a tie!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
                else if (i != players.size() - 1) { // for the bots, not the dealer
                    cout << "\n" << name << "and the dealer had the same hand. It's a tie!\n";
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
            }
        }

        // clears players' hands
        for (Player * p : players) {
            p->clearHand();
        }

        cout << "\n************************************************************************************************\n";

        while (true) {
            if (players.at(userIndex)->getMoney() < tableBuyIn)
            {
                cout << "\nYou ran out of money! :(\n\n";
                this_thread::sleep_for(chrono::milliseconds(sleepTime));
                for (int i = 0; i < numPlayers; i++) {
                    Player * p = findPlayer(i);
                    cout << "\n" << p->getPlayerName() << ":\n";
                    cout << "Total money: " << p->getMoney();
                    cout << "\nWon games: " << p->getWins();
                    cout << "\nLost games: " << p->getLosses();
                    cout << "\nTied games: " << p->getTies();
                    if (p->getLosses() != 0 || p->getWins() != 0) // prevents divide by zero error
                        cout << "\nWin percent: " << p->getWins() * 100 / (p->getLosses() + p->getWins()) << "%";
                    cout << "\nTotal rounds: " << p->getWins() + p->getLosses() + p->getTies() << endl;
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
                return;
            }
            cout << "\nWould you like to keep playing? (0 for no, 1 for yes) ";
            string keepPlaying;
            cin >> keepPlaying;
            cin.clear(); //clear the input stream
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (keepPlaying == "0") {
                for (int i = 0; i < numPlayers; i++) {
                    Player * p = findPlayer(i);
                    cout << "\n" << p->getPlayerName() << ":\n";
                    cout << "Total money: " << p->getMoney();
                    cout << "\nWon games: " << p->getWins();
                    cout << "\nLost games: " << p->getLosses();
                    cout << "\nTied games: " << p->getTies();
                    if (p->getLosses() != 0 || p->getWins() != 0) // prevents divide by zero error
                        cout << "\nWin percent: " << p->getWins() * 100 / (p->getLosses() + p->getWins()) << "%";
                    cout << "\nTotal rounds: " << p->getWins() + p->getLosses() + p->getTies() << endl;
                    this_thread::sleep_for(chrono::milliseconds(sleepTime));
                }
                return;
            }
            else if (keepPlaying == "1") {
                if (roundCounter - lastRoundShuffled > 6) {
                    unusedPile = new DeckStack(6);
                    discardPile = new DeckStack(0);
                    lastRoundShuffled = roundCounter;
                }
                break;
            }
            else {
                cout << "Invalid input, please enter 0 or 1\n";
            }
        }
    }
}

void Game::runSimulationMode() {
    lastRoundShuffled = 0;
    vector<string> names = {"You", "RandomBot", "SuperCounterBot", "ModerateCounterBot", "BasicStrategyBot1", "BasicStrategyBot2"};

    for(int i = 1; i < numPlayers; i++){
        players.push_back(new Player(amountMoney, i, names[i])); //creates the number of other players desired
    }
    random_shuffle(players.begin(), players.end(), myRandom1); //shuffles the players to have random placement around the table
    //add dealer as the last person in the vector
    players.push_back(new Player(0, 6, "Dealer"));

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

        bets = *(new vector<int> (numPlayers));
        surrendered = *(new vector <bool> (numPlayers));

        // stores the dealer
        Player * dealer = players.at(players.size() - 1);

        // deals two cards to every player
        for (Player* p : players) {
            p->giveCard(unusedPile->getTopCard());// places card in user's hand and then deletes it from unusedPile
            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
            p->giveCard(unusedPile->getTopCard());
            discard(unusedPile->removeTopCard()); //places card in discardPile cardStack
        }

        // checks if the dealer has a natural, if he does, boolean is tripped no one plays the round
        bool dealerHasNatural = dealer->getBestHand() == 21;

        // each player takes turn
        for (int i = 0; i < players.size(); i++) {
            Player * p = players.at(i);
            // adds p's bet to bets
            bets.at(i) = p->getBet(tableBuyIn);
            p->setEndTurn(false);
            p->setNatural(false);                       // sets that the player does not have a natural at the beginning of the turn
            if (p->getBestHand() == 21)                 // if you start with 21
            {
                p->setEndTurn(true);                    // your turn automatically ends
                p->setNatural(true);                    // mark they have a natural
            }

            while (!p->getEndTurn() and !dealerHasNatural) {
                // if their hand total is over 21, end turn
                if (p->getHandTotals().at(0) > 21) {
                    //getHandTotals().at(0) is the baseTotal, which is the lowest possible total
                    //if this total is already > 21, then the player busts (is out of the round)
                    p->setEndTurn(true);
                }
                else if (p->getBestHand() == 21) {
                    p->setEndTurn(true);
                }

                else {
                    // gets player action (passes in dealer's top card so user can see it)
                    int playerAction = p->takeTurn(players.at(players.size() - 1)->getHand().at(0));
                    switch (playerAction) {
                        case 1: // stand
                            stand(p);
                            break;
                        case 2: // hit
                            hit(p);
                            break;
                        case 3: // double down
                            doubleDown(p);
                            break;
                        case 4: //surrender
                            surrender(p);
                            break;
                    }
                }
            }
        }


        // runs through each player and compares their hand to the dealer
        for (int i = 0; i < players.size() - 1; i++) {
            Player * player = players.at(i);
            // if the player busts, remove their bet from their money
            // and give it to the dealer
            if (player->getBestHand() > 21) {
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
                }
                    // if the player did not get a natural, they lose
                    // the player loses his bet
                    // the dealer gets the player's bet
                else
                {
                    player->updateMoney(bets.at(i) * -1);
                    dealer->updateMoney(bets.at(i));
                    player->lostGame();
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

        if (roundCounter - lastRoundShuffled > 6) {
            unusedPile = new DeckStack(6);
            discardPile = new DeckStack(0);
            lastRoundShuffled = roundCounter;
            for (Player * p : players) {
                p->resetCounting();
            }
        }

        if (roundCounter == 500) {
            // debugging
        }

    }

    for (int i = 1; i < numPlayers; i++) {
        Player * p = findPlayer(i);
        cout << "\n" << p->getPlayerName() << ":";
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

void Game::getNumPlayers(int userGameTypeChoice) {
    if (userGameTypeChoice == 1) {
        cout << "\nHow many other players do you want in the game?\n";
        cout << "Enter an integer from 0 to 5: ";
        string input;

        while (true) {
            cin >> input;

            cin.clear(); //clear the input stream
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Check for valid user input
            if (input == "0" || input == "1" || input == "2" || input == "3" || input == "4" || input == "5") {
                numPlayers = stoi(input); //converts the char to the int value
                numPlayers++; // adding a player to account for the user running the game
                return; // this is a valid input
            }
            else {
                cout << "\nInvalid input. Please enter an integer from 0 to 5: "; //not a digit
            }
        }
    }

    else {
        cout << "\nHow many players do you want in the game?\n";
        cout << "Enter an integer from 1 to 5: ";
        string input;

        while (true) {
            cin >> input;

            cin.clear(); //clear the input stream
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (input == "1" || input == "2" || input == "3" || input == "4" || input == "5") {
                numPlayers = stoi(input); //converts the char to the int value
                numPlayers++; // adding a player to account for the user running the game
                return; // this is a valid input
            }
            else {
                cout << "\nInvalid input. Please enter an integer from 0 to 5: "; //not a digit
            }
        }
    }
}

void Game::getAmountMoney() {
    cout << "\nHow much money should each player start with?\n";
    cout << "Enter an integer between $100 and $1000000: ";
    while (true) {
        cin >> amountMoney;

        cin.clear(); //clear the input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check for valid user input
        if (amountMoney >= 100 && amountMoney <= 1000000) {
            return; //this is a valid input
        }
        else {
            cout << "\nInvalid input. Please enter an integer between $100 and $1000000: ";
        }
    }
}

void Game::getMinBet() {
    cout << "\nHow much should the minimum bet per round be?\n";
    cout << "Enter an integer between $2 and $500: ";
    while (true) {                  // while statement that error handles, printing the specific error
        cin >> tableBuyIn;
        cin.clear(); //clear the input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check for valid user input
        if ((tableBuyIn >= 2) && (tableBuyIn <= 500) && (tableBuyIn <= amountMoney)) {
            return; // this is a valid input
        }

        else {                                  // if input is not valid
            cout << "\nInvalid input, enter an integer between $2 and $500 (and below player's starting money): ";
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

