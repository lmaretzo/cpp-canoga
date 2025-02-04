/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  (New) Human Class Implementation
 ************************************************************/

#include "Human.h"
#include "Player.h"
#include <iostream>
#include <sstream>

using namespace std;

/* *********************************************************************
Function Name: Human (Constructor)
Purpose: Initializes a Human object with a given name and board size.
Parameters:
    - name: The player's name.
    - boardSize: The number of squares on the board.
Return Value: None
Reference: Inherits from Player.
********************************************************************* */
Human::Human(const string& name, int boardSize)
    : Player(name, boardSize)
{
}

/* *********************************************************************
Function Name: ~Human (Destructor)
Purpose: Cleans up a Human object.
Parameters: None
Return Value: None
Reference: Inherits from Player.
********************************************************************* */
Human::~Human()
{
}

/* *********************************************************************
Function Name: chooseSquares
Purpose: Prompts the human player to enter the squares to cover based on the dice sum.
Parameters:
    - diceSum: The total of the dice roll.
Return Value: A vector of integers representing the chosen squares.
Algorithm:
    1) Prompt the user for input.
    2) Parse the input and verify that the sum equals diceSum.
    3) Offer a hint if the input is invalid.
Reference: Overrides Player::chooseSquares.
********************************************************************* */
vector<int> Human::chooseSquares(int diceSum) {
    vector<int> chosen;
    cout << getName() << ", enter the squares you want to cover (sum must be "
        << diceSum << "): ";
    string input;
    getline(cin, input);
    stringstream ss(input);
    int num, total = 0;
    while (ss >> num) {
        chosen.push_back(num);
        total += num;
    }
    if (total != diceSum) {
        cout << "Invalid input: the numbers do not add up to " << diceSum << ".\n";
        cout << "Would you like a hint? (enter 'hint' to see the default strategy): ";
        string hintInput;
        getline(cin, hintInput);
        if (hintInput == "hint") {
            // Call the base class default strategy and display the hint.
            vector<int> hint = Player::chooseSquares(diceSum);
            cout << "Hint: Consider using the following squares: ";
            for (int s : hint)
                cout << s << " ";
            cout << "\n";
        }
        // Return an empty vector (or you could loop until valid input is provided).
        return vector<int>();
    }
    return chosen;
}
