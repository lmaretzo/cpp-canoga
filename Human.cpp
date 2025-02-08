/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  Human Class Implementation
 ************************************************************/

#include "Human.h"
#include "Player.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <cctype>
#include "InputValidator.h"
using namespace std;

/* *********************************************************************
Function Name: Human (Constructor)
Purpose: To initialize a Human object with a given name and board size.
Parameters:
         name      - a string representing the human player's name (passed by value)
         boardSize - an integer representing the number of squares on the board
Return Value: None.
Algorithm:
         1) Call the base class (Player) constructor with the provided name and board size.
Reference: None
********************************************************************* */
Human::Human(const string& name, int boardSize)
    : Player(name, boardSize)
{
    // No additional initialization required.
}

/* *********************************************************************
Function Name: ~Human (Destructor)
Purpose: To clean up a Human object.
Parameters: None.
Return Value: None.
Algorithm:
         1) Rely on the base class destructor for cleanup.
Reference: None
********************************************************************* */
Human::~Human()
{
    // No explicit cleanup needed.
}


/* *********************************************************************
Function Name: decideMove
Purpose: To prompt the human player for a move decision based on the dice roll
         and the opponent's board state. The function offers a hint if requested,
         forces covering if uncovering is not allowed, and validates the input.
Parameters:
         diceSum      - an integer representing the total from the dice roll
         opponent     - a constant reference to the opponent Player object
         allowUncover - a boolean flag indicating whether uncovering opponent's squares
                        is permitted this turn (false on first turn of the first player)
Return Value: A MoveDecision structure containing the decision (cover/uncover)
              and the chosen squares.
Algorithm:
         1) Prompt the user for a hint; if requested, compute and display a hint.
         2) If allowUncover is false, force covering and notify the user.
         3) Otherwise, prompt the user to choose between covering and uncovering.
         4) Prompt the user to enter the squares (as a space-separated string).
         5) If input is empty, indicate that no move was made and return an empty decision.
         6) Parse the input string into integers and accumulate their sum.
         7) If a 0 is encountered, interpret it as a skip signal and return an empty decision.
         8) If the total does not equal diceSum, display an error message and return an empty decision.
         9) Otherwise, store the chosen squares in the MoveDecision and return it.
Reference: AI ASSISTED
********************************************************************* */

MoveDecision Human::decideMove(int diceSum, const Player& opponent, bool allowUncover) {
    MoveDecision decision;
    // First, ask if the user wants a hint.
    bool wantHint = InputValidator::getYesNo("Would you like a hint for your move? (y/n): ");
    if (wantHint) {
        MoveDecision hintDecision = Player::decideMove(diceSum, opponent, allowUncover);
        if (!hintDecision.squares.empty()) {
            cout << "Hint: Consider using the move: ";
            cout << (hintDecision.cover ? "cover " : "uncover ");
            for (int s : hintDecision.squares)
                cout << s << " ";
            cout << "\n";
            if (!hintDecision.explanation.empty()) {
                cout << "Explanation: " << hintDecision.explanation << "\n";
            }
        }
        else {
            cout << "No valid hint available.\n";
        }
    }

    // Now use InputValidator to ask if the user wants to cover.
    // (Yes = cover; No = uncover.)
    bool cover;
    // Use the passed flag to force covering if uncovering is not allowed.
    if (!allowUncover) {
        cover = true;
        cout << "Uncovering is not allowed on your first turn. You will cover squares." << "\n";
    }
    else {
        cover = InputValidator::getYesNo("Do you want to cover your squares? (y for cover, n for uncover): ");
    }
    decision.cover = cover;

    // Prompt the user for the move.
    cout << "Enter your move (e.g. '5 7') for "
        << (cover ? "cover" : "uncover")
        << " (the numbers must sum to " << diceSum << "): ";
    string input;
    getline(cin, input);
    if (input.empty()) {
        cout << "No input provided. Skipping turn.\n";
        decision.squares.clear();
        return decision;
    }
    stringstream ss(input);
    vector<int> chosen;
    int num, total = 0;
    while (ss >> num) {
        if (num == 0) {
            cout << getName() << " chose to skip their turn.\n";
            decision.squares.clear();
            return decision;
        }
        chosen.push_back(num);
        total += num;
    }
    if (total != diceSum) {
        cout << "Invalid move: the numbers do not add up to " << diceSum << ". Skipping turn.\n";
        decision.squares.clear();
        return decision;
    }
    decision.squares = chosen;
    return decision;
}

