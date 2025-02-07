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

// New interactive decision method for the human player.
MoveDecision Human::decideMove(int diceSum) {
    MoveDecision decision;
    // Ask the user whether they want to cover or uncover.
    char moveType;
    while (true) {
        cout << getName() << ", do you want to cover your squares or uncover your opponent's squares? (c/u): ";
        cin >> moveType;
        moveType = tolower(moveType);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (moveType == 'c' || moveType == 'u')
            break;
        cout << "Invalid input. Please enter 'c' or 'u'.\n";
    }
    decision.cover = (moveType == 'c');

    // Now, prompt for the move.
    while (true) {
        cout << getName() << ", enter the squares you want to " << (decision.cover ? "cover" : "uncover") << " (sum must be " << diceSum << "):\n";
        cout << "Type your move or type 'hint' to see the recommended move: ";
        string input;
        getline(cin, input);

        if (input == "hint") {
            MoveDecision hintDecision = Player::decideMove(diceSum);
            if (!hintDecision.squares.empty()) {
                cout << "Hint: Consider using the following squares: ";
                for (int s : hintDecision.squares)
                    cout << s << " ";
                cout << "\n";
            }
            else {
                cout << "No valid hint available.\n";
            }
            continue; // reprompt
        }
        if (input.empty()) {
            cout << "No input provided. Please try again.\n";
            continue;
        }
        stringstream ss(input);
        vector<int> chosen;
        int num, total = 0;
        while (ss >> num) {
            if (num == 0) {  // If the user enters 0, treat it as a skip.
                cout << getName() << " chose to skip their turn.\n";
                decision.squares = vector<int>(); // empty move means skip
                return decision;
            }
            chosen.push_back(num);
            total += num;
        }
        if (total != diceSum) {
            cout << "Invalid input: the numbers do not add up to " << diceSum
                << ". Please try again or type 'hint' for assistance.\n";
            continue;
        }
        decision.squares = chosen;
        return decision;
    }
}