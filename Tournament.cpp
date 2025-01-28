#include "Tournament.h"
#include "Round.h"
#include <iostream>
#include "InputValidator.h"

using namespace std;

Tournament::Tournament()
    : boardSize(9) // Default board size; updated later in initializeBoardSize
{
}

Tournament::~Tournament()
{
}

// Function to initialize the board size
void Tournament::initializeBoardSize()
{
    cout << "Enter the board size (9, 10, or 11): ";
    while (true)
    {
        cin >> boardSize;
        if (boardSize >= 9 && boardSize <= 11)
            break;
        cout << "Invalid input. Please enter 9, 10, or 11: ";
    }
}

void Tournament::start()
{
    cout << "=== Welcome to Basic Canoga Game ===\n";
    cout << "We will play a few rounds until you decide to stop.\n";

    // Initialize board size based on user input
    initializeBoardSize();

    // Create the players using the chosen board size
    Player human("Human", false, boardSize);
    Player computer("Computer", true, boardSize);

    bool keepPlaying = true;
    while (keepPlaying)
    {
        // Create a Round and play it
        Round round(human, computer, dice, boardSize); // Pass boardSize to Round
        round.play();

        // Show scores
        cout << "\nCurrent Scores:\n";
        cout << human.getName() << ": " << human.getScore() << "\n";
        cout << computer.getName() << ": " << computer.getScore() << "\n";

        // Ask the user if they want to play another round
        keepPlaying = InputValidator::getYesNo("\nPlay another round? (y/n): ");
    }

    // Display final scores and determine the winner
    cout << "\n=== Final Scores ===\n";
    cout << human.getName() << ": " << human.getScore() << "\n";
    cout << computer.getName() << ": " << computer.getScore() << "\n";

    if (human.getScore() > computer.getScore())
        cout << "=> Human wins the tournament!\n";
    else if (computer.getScore() > human.getScore())
        cout << "=> Computer wins the tournament!\n";
    else
        cout << "=> It's a draw!\n";

    cout << "Thank you for playing!\n";
}

void Tournament::enableManualDiceMode()
{
    dice.enableManualMode();
}

void Tournament::disableManualDiceMode()
{
    dice.disableManualMode();
}
