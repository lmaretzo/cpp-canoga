#include "Tournament.h"
#include "InputValidator.h" // Include the new utility class for validation
#include "Round.h"


using namespace std;




int main() {


    Tournament tour;

    // Enable manual dice mode based on user input.
    if (getYesNo("Enable manual dice mode for testing? (y/n): ")) {
        tour.enableManualDiceMode(); // Enable manual mode in the tournament.
    }

    // Prompt user to resume a saved game.
    if (getYesNo("Do you want to resume a saved game? (y/n): ")) {
        bool loaded = false; // flag to check if loading succeeded
        while (!loaded) {
            cout << R"(Enter file path with filename ex: C:\Users\savedGame.txt to load game: )";
            string filename;
            getline(cin, filename);
            // Attempt to load the game.
            if (tour.loadGame(filename)) {
                loaded = true;
            }
            else {
                // If loading failed, ask the user if they want to try again.
                if (!getYesNo("Error loading file. Would you like to try again? (y/n): ")) {
                    cout << "Failed to load game. Starting a new game...\n";
                    break;
                }
            }
        }
    }

    tour.start();
    return 0;
}