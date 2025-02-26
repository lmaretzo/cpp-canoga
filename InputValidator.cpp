#include "InputValidator.h"
using namespace std;

/* *********************************************************************
Function Name: getYesNo
Purpose: Ensures the user enters a valid yes ('y') or no ('n') response.
Parameters:
    - prompt: A string message to display to the user.
Return Value:
    - Boolean: Returns true if 'y' is entered, false if 'n' is entered.
Algorithm:
    1) Display the prompt message.
    2) Read user input.
    3) Normalize input to lowercase.
    4) Validate input (only 'y' or 'n' is accepted).
    5) If invalid, prompt again.
Reference: None
********************************************************************* */
bool getYesNo(const string& prompt) {
    char userChoice;
    while (true) {
        cout << prompt;
        cin >> userChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Normalize input to lowercase
        userChoice = tolower(static_cast<unsigned char>(userChoice));

        if (userChoice == 'y') return true;
        if (userChoice == 'n') return false;

        cout << "Invalid input. Please enter 'y' for yes or 'n' for no.\n";
    }
}
