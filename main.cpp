/*
 * COP3503 Semester Project
 * Spring 2018
 *
 * Blackjack
 *
 * Project Team 55
 * by Nicolas Azcarate, Gregory DeCanio, Asher Johnson Hogan,
 * Colby Lathrop, Spencer Warren, and Davis Washburn
 *
 * main.cpp
 *
 */

#include <iostream>
#include "DeckStack.h"
#include "Game.h"
//#include <thread>
//#include <chrono>

using namespace std;
int userGameTypeChoice = 0;


void printInstructions(){
    cout << "- The object of the game is to beat the dealer by getting a hand total as close to 21 as possible, without going over 21\n"
            "- Face cards are worth 10 points, Aces are worth 1 or 11 points, and all other cards are worth their individual point value.\n"
            "- Before each round, the player places a bet (usually between $2 and $500).\n"
            "- Once all the bets have been placed, the Dealer will give one card, face up, to each player and himself.\n"
            "- Another round is dealt, each player receiving a face up card, but the dealer receives a face down card.\n\n";

    cout << "- Each player then has the option to:\n"
                "\t- \"stand\" (end your turn)\n"
                "\t- \"hit\" (ask for another card in the hopes of getting close to, or on, 21)\n"
                "\t- \"double down\" (at the beginning of your turn, double your bet, but only receive one more card)\n"
                "\t- \"surrender\" (at the beginning of your turn, lose half of your bet and end your turn)\n\n";

    cout << "- At the end of the round the dealer will play. If they bust (go above 21), you win, and the dealer will pay you 1:1 what you originally bet.\n"
            "- If a player gets a hand total over 21, they bust and automatically lose the round and their bet.\n";
            "- If the dealer doesn't bust but is higher than your hand total, the dealer wins and keeps your bet.\n"
            "- If the dealer doesn't bust and is lower than your hand total, the dealer loses and will pay you 1:1 what you originally bet.\n"
            "- If you and the dealer have the same hand totals, there is a tie and no money is paid out.\n\n";

    cout << "- A \"natural\" is when a player is initially dealt 21 in their first two cards.\n"
                "\t - If the player has a natural, they win 1.5 times their original bet.\n"
                "\t - If the dealer has a natural, the round ends and the dealers takes all bets.\n"
                "\t - If both the player and dealer have a neutral, there is a tie and no money is paid out.\n\n";

//    cout << "- If the dealer is showing an Ace, a player can \"purchase insurance\", which costs half of your bet \n"
//                "\t - If the dealer has a natural 21, then the player loses the original bet but is paid 2:1 on the insurance bet\n"
//                "\t - If the dealer doesn't have a natural 21, then the player loses the insurance bet and the round continues\n\n";
}

void beginTutorial()
{
    bool responseBool = true;       // is true when firstTime is not a valid input, turns false when it becomes "Yes" or "No"
    bool learnYes = false;          // tracks if user wants to see rules or not (true for rules, false for no rules)
    string firstTime;               // holds users response to if it is their first time playing (should be "Yes" or "No")
    string learnToPlay;             // holds user response to if they would like to learn to play or not (should be "Yes" or "No")

    cout << "\nIs this your first time playing? (Yes or No): ";
    cin >> firstTime;

    cin.clear(); //clear the input stream
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    transform(firstTime.begin(), firstTime.end(), firstTime.begin(), ::tolower);

    while (responseBool)
    {
        if (firstTime == "yes")
        {
            responseBool = false;           // can now exit the loop asking if it is their first time
            bool responseLearn = true;      // this variable tracks if the user has an appropriate response to "would you like to play"
            cout << "\nAwesome! Would you like to learn how to play? (Yes or No): ";
            cin >> learnToPlay;

            cin.clear(); //clear the input stream
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            transform(learnToPlay.begin(), learnToPlay.end(), learnToPlay.begin(), ::tolower);

            while (responseLearn)
            {
                if (learnToPlay == "yes")
                {
                    cout << "\nWonderful! We'll give you a brief overview of the rules and how to play!\n\n";
                    responseLearn = false;       // can now exit the loop asking if they would like to learn how to play
                    learnYes = true;             // activates that they must be given the rules
                }
                else if (learnToPlay == "no")
                {
                    cout << "\nRisky?! We like it!\n";
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
        else if (firstTime == "no")
        {
            cout << "\nGreat! Let's get right to it then!\n";
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
        printInstructions();
    }
}

void beginMenu(){
    bool programRun = true;
    int sleepTime = 100;
    cout << "\nWelcome to BlackJack!\n\n"
            "The object of the game is to beat the dealer by getting a hand total as close to 21 as possible, without going over 21\n"
            "\tIn order to enhance the user experience, we have included bots for you to play against so you can see how well you match up against them!\n"
            "\tBot 1: Randomly chooses to stand, hit, or double down\n"
            "\tBot 2: An incredible card counter that remembers each card that has been dealt before the deck is reshuffled!\n"
            "\tBot 3: A weaker card counter that uses the traditional halves method for tracking the running count of the table\n"
            "\tBot 4: Uses a traditional playing strategy for when they have a \"soft\" hand\n"
            "\tBot 5: Uses a traditional playing strategy for when they have a \"hard\" hand\n"
            "\t\tWe hope you enjoy!\n\n";
    cout << "\n";
    this_thread::sleep_for(chrono::milliseconds(250));
    cout << "     .-~~-.             /\\               /\\           .-~~~-__-~~~-. \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "    {      }          .'  `.           .'  `.        {              }\n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << " .-~-.    .-~-.     .'      `.        '      `.       `.          .' \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "{              }   <          >    .'          `.       `.      .'   \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << " `.__.'||`.__.'     `.      .'    {              }        `.  .'     \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "       ||             `.  .'       ~-...-||-...-~           \\/      \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "      '--`              \\/               ||                          \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "                                        '--`                         \n";
    while (programRun) {
        cout << "You may run either:\n";
        cout << "\t1) Playing mode: play rounds of Blackjack against a dealer and other players\n";
        cout << "\t2) Simulation mode: run many simulations to test effectiveness of playing styles between our bots\n";

        cout << "Enter 1 or 2: ";
        cin >> userGameTypeChoice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //Check for valid user input
        switch (userGameTypeChoice) {
            case 1: {
                //Exit loop with valid input
                beginTutorial();            // asks the user if they would like to hear the rules of blackjack
                programRun = false;
                break;
            }

            case 2: {
                //Exit loop with valid input
                programRun = false;
                break;
            }
            default: {
                cout << "\nInvalid input, please enter a 1 or 2: ";
                //clears the input stream to allow the user to input an acceptable value
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

int main() {
    srand (unsigned (time(0)));
    beginMenu();                // asks the user which mode they want to run (playing or simulation)
    Game game(userGameTypeChoice);
}
