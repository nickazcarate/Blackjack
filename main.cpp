using namespace std;
#include <iostream>
#include "Card.h"
#include "DeckStack.h"
#include "Game.h"
#include <thread>
#include <chrono>

int numPlayers = 0;
int userGameTypeChoice = 0;

int beginMenu(){
    //cout << "\nWelcome to Blackjack!\n\n";
    this_thread::sleep_for(chrono::milliseconds(600));
    bool programRun = true;
    while (programRun) {
        cout << "You may run either:\n";
        cout << "\t1) Playing mode: play rounds of Blackjack against a dealer and other players\n";
        cout << "\t2) Simulation mode: run many simulations to test effectiveness of playing styles between our bots\n";
        this_thread::sleep_for(chrono::milliseconds(600));
        cout << "Enter 1 or 2: ";
        cin >> userGameTypeChoice;

        //Check for valid user input
        switch (userGameTypeChoice) {
            case 1: {
                //Exit loop with valid input
                programRun = false;
                break;
            }

            case 2: {
                //Exit loop with valid input
                programRun = false;
                break;
            }
            default: {
                cout << "\nPlease enter a valid choice. ";
                //clears the input stream to allow the user to input an acceptable value
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

void beginTutorial()
{
    bool responseBool = true;       // is true when firstTime is not a valid input, turns false when it becomes "Yes" or "No"
    bool learnYes = false;          // tracks if user wants to see rules or not (true for rules, false for no rules)
    string firstTime;               // holds users response to if it is their first time playing (should be "Yes" or "No")
    string learnToPlay;             // holds user response to if they would like to learn to play or not (should be "Yes" or "No")
    cout << "\nWelcome to BlackJack!\n\n"
            "Is this your first time playing? (Yes or No)";
    cin >> firstTime;
    transform(firstTime.begin(), firstTime.end(), firstTime.begin(), ::tolower);

    while (responseBool)
    {
        if (firstTime.compare("yes") == 0)
        {
            responseBool = false;           // can now exit the loop asking if it is their first time
            bool responseLearn = true;      // this variable tracks if the user has an appropriate response to "would you like to play"
            cout << "\nAwesome! Would you like to learn how to play? (Yes or No)";
            cin >> learnToPlay;
            transform(learnToPlay.begin(), learnToPlay.end(), learnToPlay.begin(), ::tolower);

            while (responseLearn)
            {
               if (learnToPlay.compare("yes") == 0)
               {
                   cout << "\nWonderful! We'll give you a brief overview of the rules and how to play!";
                   responseLearn = false;       // can now exit the loop asking if they would like to learn how to play
                   learnYes = true;             // activates that they must be given the rules
               }
               else if (learnToPlay.compare("no") == 0)
               {
                   cout << "\nRisky?! We like it!";
                   return;                      // no further action needed. Exit can go to the menu
               }
               else
               {
                   cout << "\nPlease enter a valid choice.";
                   cin.clear();        // clears input stream
                   cin.ignore(numeric_limits<streamsize>::max(), '\n');
                   cin >> learnToPlay;
               }
            }
        }
        else if (firstTime.compare("no") == 0)
        {
            cout << "\nGreat! Let's get right to it then!";
            return;                             // no further action needed. Exit can go to the menu
        }
        else
        {
            cout << "\nPlease enter a valid choice.";
            cin.clear();                        // clears input stream
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> firstTime;
            transform(firstTime.begin(), firstTime.end(), firstTime.begin(), ::tolower);
        }
    }
    if (learnYes)               // if true, states the rules of BlackJack
    {
        cout << "The object of the game is to beat the dealer by getting a count as close to 21 as possible, without going over 21\n";
        cout << "Aces are worth 1 or 11 points, face cards are worth 10 points, and all other cards are worth their individual point value.\n";
        cout << "Before each deal, the player places a bet (usually between $2 and $500).\n";
        cout << "Once all the bets have been placed, the dealer will give one card, face up, to each player and himself.\n";
        cout << "Another round is dealt, each player receiving a face up card, while the dealer receives a face down card.\n";
        cout << "A \"natural\" is when a player's first two cards total to 21.\n";
        cout << "If the player has a natural, they win 1.5 times their original bet. If the dealer has a natural, the round ends and the dealers takes all bets.\n";
        cout << "You, the player, will go first, followed by the computers. You have the option to \"stand\" (not ask for another card),\n"
                "\"hit\" (ask for another card in the hopes of getting close to, or on, 21), or \"double down\" (double your bet, but only receive one more card).\n"
                "If you, the player, get a hand total over 21, you bust, and automatically lose the round, and your bet.\n"
                "If it is the first round, you have not done anyting yet, and the dealer is showing an ace or ten-card, you can \"purchase insurance\" "
                "(take half of your bet back, but end the round for yourself).\n"
                "At the end of the round the dealer will play. If they bust (go above 21), you win, and the dealer will pay you what you originally bet.\n"
                "If the dealer is below 21, but higher than your hand total, the dealer wins and keeps your bet.\n"
                "If the dealer is below 21, and lower than your hand total, the dealer loses and will pay you what you originally bet.\n"
                "If you and the dealer have the same hand totals, there is a tie, and all initial bets are given back.\n";
    }
}
int main() {
    srand (unsigned (time(0)));
    beginTutorial();            // asks the user if they would like to hear the rules of blackjack
    beginMenu();                // asks the user which mode they want to run (playing or simulation)
    Game game(userGameTypeChoice);
}