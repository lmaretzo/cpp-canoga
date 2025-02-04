/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#include "InputValidator.h"

using namespace std;

/* *********************************************************************
Function Name: getYesNo
Purpose: Prompts the user with a yes/no question and validates the input.
Parameters:
    - prompt: A string that contains the question to ask the user.
Return Value: A boolean value:
    - Returns true if the user inputs 'y' (yes).
    - Returns false if the user inputs 'n' (no).
Algorithm:
    1) Display the prompt message.
    2) Read the user's input.
    3) Normalize input to lowercase.
    4) If the input is 'y', return true.
    5) If the input is 'n', return false.
    6) If input is invalid, prompt the user again.
Reference: None
********************************************************************* */
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
