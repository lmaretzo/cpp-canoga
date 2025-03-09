/************************************************************
 * Name:     Lucas Maretzo
 * Project:  P1 Canoga
 * Class:    CMPS366 Operating Systems
 * Date:     3/10/2025
 ************************************************************/

#include "Tournament.h"
#include "InputValidator.h"
#include "Round.h"

using namespace std;

/* *********************************************************************
Function Name: main
Purpose: Entry point for the Canoga game application.
Parameters: None.
Return Value: An integer (0) indicating successful program execution.
Algorithm:
         1) Create a Tournament object.
         2) Optionally enable manual dice mode for testing.
         3) Optionally load a saved game.
         4) Start the tournament.
         5) Return 0 to indicate successful execution.
Reference: None
********************************************************************* */
int main() {
    // Create tournament object
    Tournament tour;

    // Enable manual dice mode based on user input
    if (getYesNo("Enable manual dice mode for testing? (y/n): ")) {
        tour.enableManualDiceMode(); // Enable manual mode in the tournament
    }

    // Prompt user to resume a saved game
    if (getYesNo("Do you want to resume a saved game? (y/n): ")) {
        bool loaded = false; // Flag to check if loading succeeded

        while (!loaded) {
            cout << R"(Enter file path with filename ex: C:\Users\savedGame.txt to load game: )";

            // Get filename from user
            string filename;
            getline(cin, filename);

            // Attempt to load the game
            if (tour.loadGame(filename)) {
                loaded = true;
            }
            else {
                // If loading failed, ask the user if they want to try again
                if (!getYesNo("Error loading file. Would you like to try again? (y/n): ")) {
                    cout << "Failed to load game. Starting a new game...\n";
                    break;
                }
            }
        }
    }
    // Start the tournament
    tour.start();

    return 0;
}