#include "Tournament.h"
#include "InputValidator.h" // Include the new utility class for validation
#include "Round.h"

using namespace std;

int main() {
    Tournament tour;
    
    // Enable manual dice mode based on user input.
    if (InputValidator::getYesNo("Enable manual dice mode for testing? (y/n): ")) {
        tour.enableManualDiceMode(); // Enable manual mode in the tournament.
    }
    
    // Prompt user to resume a saved game.
    if (InputValidator::getYesNo("Do you want to resume a saved game? (y/n): ")) {
        cout << "Enter the filename to load: ";
       string filename;
       getline(cin, filename);
        if (tour.loadGame(filename)) {
            cout << "Game loaded successfully!\n";
            // If you want to print debug info, call the debug getters or a debug method.
            cout << "Computer board: ";
            tour.getComputer().printBoard();
            cout << "Human board: ";
            tour.getHuman().printBoard();
            cout << "First Turn: " << (tour.getFirstTurnIsHuman() ? "Human" : "Computer") << "\n";
            cout << "Next Turn: " << tour.getNextTurn() << "\n";
            cout << "\nCurrent Scores:" << endl;
            cout << "Human: " << tour.getHuman().getScore() << endl;
            cout << "Computer: " << tour.getComputer().getScore() << endl;

        }
        else {
            cout << "Failed to load game. Starting a new game...\n";
        }
    }

    tour.start();
    return 0;
}