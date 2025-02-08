/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  (New) Human Class Implementation
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

