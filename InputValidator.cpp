#include "InputValidator.h"

using namespace std;

bool InputValidator::getYesNo(const string& prompt) {
    char userChoice;
    bool validInput = false;

    while (!validInput) {
        cout << prompt;
        cin >> userChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        // Normalize input to lowercase
        userChoice = tolower(userChoice);

        if (userChoice == 'y') {
            return true; // Yes
        }
        else if (userChoice == 'n') {
            return false; // No
        }
        else {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no.\n";
        }
    }

    // This return is redundant but avoids compiler warnings
    return false;
}
