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
string userGameTypeChoice;


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
            "- If a player gets a hand total over 21, they bust and automatically lose the round and their bet.\n"
            "- If the dealer doesn't bust but is higher than your hand total, the dealer wins and keeps your bet.\n"
            "- If the dealer doesn't bust and is lower than your hand total, the dealer loses and will pay you 1:1 what you originally bet.\n"
            "- If you and the dealer have the same hand totals, there is a tie and no money is paid out.\n\n";

    cout << "- A \"natural\" is when a player is initially dealt 21 in their first two cards.\n"
                "\t - If the player has a natural, they win 1.5 times their original bet.\n"
                "\t - If the dealer has a natural, the round ends and the dealers takes all bets.\n"
                "\t - If both the player and dealer have a natural, there is a tie and no money is paid out.\n\n";

//    cout << "- If the dealer is showing an Ace, a player can \"purchase insurance\", which costs half of your bet \n"
//                "\t - If the dealer has a natural 21, then the player loses the original bet but is paid 2:1 on the insurance bet\n"
//                "\t - If the dealer doesn't have a natural 21, then the player loses the insurance bet and the round continues\n\n";
}

void beginTutorial()
{
    bool responseBool = true;       // is true when firstTime is not a valid input, turns false when it becomes "Yes" or "No"
    bool learnYes = false;          // tracks if user wants to see rules or not (true for rules, false for no rules)
    string firstTime;               // holds users response to if it is their first time playing (should be "1" or "2")
    string learnToPlay;             // holds user response to if they would like to learn to play or not (should be "1" or "2")

    cout << "\nIs this your first time playing? Enter 1 (Yes) or 2 (No): ";

    while (responseBool)
    {
        cin >> firstTime;

        cin.clear(); //clear the input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (firstTime == "1")
        {
            responseBool = false;           // can now exit the loop asking if it is their first time
            bool responseLearn = true;      // this variable tracks if the user has an appropriate response to "would you like to play"
            cout << "\nAwesome! Would you like to learn how to play? Enter 1 (Yes) or 2 (No): ";

            while (responseLearn)
            {
                cin >> learnToPlay;

                cin.clear(); //clear the input stream
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (learnToPlay == "1")
                {
                    cout << "\nWonderful! We'll give you a brief overview of the rules and how to play!\n\n";
                    responseLearn = false;       // can now exit the loop asking if they would like to learn how to play
                    learnYes = true;             // activates that they must be given the rules
                }
                else if (learnToPlay == "2")
                {
                    cout << "\nRisky?! We like it!\n";
                    return;                      // no further action needed. Exit can go to the menu
                }
                else
                {
                    cout << "\nInvalid input, please enter 1 (Yes) or 2 (No): ";
                }
            }
        }
        else if (firstTime == "2")
        {
            cout << "\nGreat! Let's get right to it then!\n";
            return;                             // no further action needed. Exit can go to the menu
        }
        else
        {
            cout << "\nInvalid input, please enter 1 (Yes) or 2 (No): ";
        }
    }

    if (learnYes)               // if true, states the rules of BlackJack
    {
        printInstructions();
    }
}

void printBlackJack(){
    cout << "\n\n\t\t ________      ___           ________      ________      ___  __           ___      ________      ________      ___  __       \n"
            "\t\t|\\   __  \\    |\\  \\         |\\   __  \\    |\\   ____\\    |\\  \\|\\  \\        |\\  \\    |\\   __  \\    |\\   ____\\    |\\  \\|\\  \\     \n"
            "\t\t\\ \\  \\|\\ /_   \\ \\  \\        \\ \\  \\|\\  \\   \\ \\  \\___|    \\ \\  \\/  /|_      \\ \\  \\   \\ \\  \\|\\  \\   \\ \\  \\___|    \\ \\  \\/  /|_   \n"
            "\t\t \\ \\   __  \\   \\ \\  \\        \\ \\   __  \\   \\ \\  \\        \\ \\   ___  \\   __ \\ \\  \\   \\ \\   __  \\   \\ \\  \\        \\ \\   ___  \\  \n"
            "\t\t  \\ \\  \\|\\  \\   \\ \\  \\____    \\ \\  \\ \\  \\   \\ \\  \\____    \\ \\  \\\\ \\  \\ |\\  \\\\_\\  \\   \\ \\  \\ \\  \\   \\ \\  \\____    \\ \\  \\\\ \\  \\ \n"
            "\t\t   \\ \\_______\\   \\ \\_______\\   \\ \\__\\ \\__\\   \\ \\_______\\   \\ \\__\\\\ \\__\\\\ \\________\\   \\ \\__\\ \\__\\   \\ \\_______\\   \\ \\__\\\\ \\__\\\n"
            "\t\t    \\|_______|    \\|_______|    \\|__|\\|__|    \\|_______|    \\|__| \\|__| \\|________|    \\|__|\\|__|    \\|_______|    \\|__| \\|__|\n\n" ;

}

void printCardSymbols(){
    int sleepTime = 100;
    cout << "\n";
    this_thread::sleep_for(chrono::milliseconds(250));
    cout << "\t\t\t     .-~~-.      \t\t\t\t       /\\       \t\t\t\t        /\\       \t\t\t\t   .-~~~-__-~~~-. \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "\t\t\t    {      }     \t\t\t\t     .'  `.      \t\t\t\t      .'  `.      \t\t\t\t  {              }\n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "\t\t\t .-~-.    .-~-.  \t\t\t\t   .'      `.    \t\t\t\t    .'      `.    \t\t\t\t   `.          .' \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "\t\t\t{              } \t\t\t\t  <          >   \t\t\t\t  .'          `.  \t\t\t\t     `.      .'   \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "\t\t\t `.__.'||`.__.'  \t\t\t\t   `.      .'    \t\t\t\t {              } \t\t\t\t       `.  .'     \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "\t\t\t       ||        \t\t\t\t     `.  .'      \t\t\t\t  ~-...-||-...-~  \t\t\t\t         \\/      \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "\t\t\t      '--`       \t\t\t\t       \\/       \t\t\t\t        ||        \t\t\t\t                   \n";
    this_thread::sleep_for(chrono::milliseconds(sleepTime));
    cout << "\t\t\t                 \t\t\t\t                 \t\t\t\t       '--`       \t\t\t\t                  \n";
}


void beginMenu(){
    bool programRun = true;

    printBlackJack();

    cout << "\nWelcome to BlackJack!\n\n"
            "The object of the game is to beat the dealer by getting a hand total as close to 21 as possible, without going over 21\n"
            "\tIn order to enhance the user experience, we have included bots for you to play against so you can see how well you match up against them!\n"
            "\tBot 1: Randomly chooses to stand, hit, or double down\n"
            "\tBot 2: An incredible card counter that remembers each card that has been dealt before the deck is reshuffled!\n"
            "\tBot 3: A weaker card counter that uses the traditional halves method for tracking the running count of the table\n"
            "\tBot 4: Uses a traditional playing strategy for when they have a \"soft\" hand\n"
            "\tBot 5: Uses a traditional playing strategy for when they have a \"hard\" hand\n"
            "\t\tWe hope you enjoy!\n\n";

    printCardSymbols();

        cout << "You may run either:\n";
        cout << "\t1) Playing mode: play rounds of Blackjack against a dealer and other players\n";
        cout << "\t2) Simulation mode: run many simulations to test effectiveness of playing styles between our bots\n";
        cout << "\t3) Demo mode: let us show you how naturals work!\n";
        cout << "Enter 1 or 2 or 3: ";

    while(programRun){
        cin >> userGameTypeChoice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //Check for valid user input
        if(userGameTypeChoice == "1"){
            //Exit loop with valid input
            beginTutorial();            // asks the user if they would like to hear the rules of blackjack
            break;
        }

        else if (userGameTypeChoice == "2"){
            //Exit loop with valid input
            break;
        }
        else if (userGameTypeChoice == "3"){
            // Exit loop with valid input
            break;
        }
        else{
            cout << "\nInvalid input, please enter a 1 or 2 or 3: ";
        }
    }
}

int main() {
    srand (unsigned (time(0)));
    beginMenu();                // asks the user which mode they want to run (playing or simulation)
    int choice = stoi(userGameTypeChoice);
    Game game(choice);
}
