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
#include "Tournament.h" 

using namespace std;

/* *********************************************************************
Function Name: Human (Constructor)
Purpose: To initialize a Human object with a given name and board size.
Parameters:
         name         - a string representing the human player's name (passed by value)
         boardSize    - an integer representing the number of squares on the board
         tournament   - a pointer to the Tournament object (optional)
Return Value: None.
Algorithm:
         1) Call the base class (Player) constructor with the provided name and board size.
         2) Initialize the tournamentPtr with the provided tournament pointer.
Reference: AI
********************************************************************* */
Human::Human(const string& name, int boardSize, Tournament* tournament)
    : Player(name, boardSize), tournamentPtr(tournament)
{
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
}

/* *********************************************************************
Function Name: decideMove
Purpose: To prompt the human player for a move decision based on the dice roll
         and the opponent's board state.
Parameters:
         diceSum       - an integer representing the total from the dice roll
         opponent      - a constant reference to the opponent Player object
         allowUncover  - a boolean flag indicating whether uncovering opponent's squares
                         is permitted this turn (false on first turn of the first player)
         tournamentPtr - a pointer to the Tournament object for handicap info
Return Value: A MoveDecision structure containing the decision (cover/uncover)
              and the chosen squares.
Algorithm:
         1) Prompt the user for a hint; if requested, compute and display a hint.
         2) Check if uncovering is allowed based on opponent board and handicap rules.
         3) Force covering if necessary, or prompt user to choose.
         4) Read and validate the move input to ensure squares sum to diceSum.
         5) Return the constructed MoveDecision.
Reference: AI
********************************************************************* */
MoveDecision Human::decideMove(int diceSum, const Player& opponent, bool allowUncover, const Tournament* tournamentPtr) {
    MoveDecision decision;

    // First, ask if the user wants a hint.
    bool wantHint = getYesNo("Would you like a hint for your move? (y/n): ");
    if (wantHint) {
        MoveDecision hintDecision = Player::decideMove(diceSum, opponent, allowUncover, tournamentPtr);
        if (!hintDecision.squares.empty()) {
            if (!hintDecision.explanation.empty()) {
                cout << "Hint: " << hintDecision.explanation << "\n";
            }
        }
        else {
            cout << "No valid hint available.\n";
        }
    }

    // Check if the opponent has any covered squares
    bool opponentHasCoveredSquares = false;
    vector<int> oppSquares = opponent.getSquares();
    for (int sq : oppSquares) {
        if (sq != 0) {
            opponentHasCoveredSquares = true;
            break;
        }
    }

    // Check for handicap protection
    bool handicapBlocking = tournamentPtr && tournamentPtr->getHandicapActive() &&
        opponent.getName() == tournamentPtr->getAdvantagePlayerName() &&
        !opponent.getHasHadTurnInRound();

    // Force covering in these cases:
    bool forceCovering = false;
    string reasonMessage = "";

    // Use the centralized function to determine if uncovering is allowed
    if (!opponentHasCoveredSquares || handicapBlocking || !canUncover(diceSum, opponent, tournamentPtr)) {
        forceCovering = true;
    }

    // Determine if user covers or uncovers
    bool cover;
    if (forceCovering) {
        cover = true;
        cout << reasonMessage << "You must cover your own squares." << endl;
    }
    else {
        cover = getYesNo("Do you want to cover your squares? (y for cover, n for uncover): ");
    }
    decision.cover = cover;

    // Get the user's move
    while (true)
    {
        cout << "Enter your move (e.g. '5 7') for "
            << (decision.cover ? "cover" : "uncover")
            << " (the numbers must sum to " << diceSum << ", or 0 to skip): ";

        // Read the entire line
        string input;
        getline(cin, input);

        if (input.empty())
        {
            // Check if this is the player's first turn in the round
            if (!getHasHadTurnInRound()) {
                cout << "Cannot skip on your first turn of the round. Please enter a valid move.\n";
                continue; // Re-prompt for input
            }
            else {
                cout << "No input provided. Skipping turn.\n";
                decision.squares.clear();
                return decision;
            }
        }

        // Parse the squares
        stringstream ss(input);
        vector<int> chosen;
        int num, total = 0;
        bool skip = false;

        while (ss >> num)
        {
            if (num == 0)
            {
                // Check if this is the player's first turn in the round
                if (!getHasHadTurnInRound()) {
                    cout << "Cannot skip on your first turn of the round. Please enter a valid move.\n";
                    skip = true;
                    break; // Exit the parsing loop
                }
                else {
                    // skip signal
                    cout << getName() << " chose to skip their turn.\n";
                    decision.squares.clear();
                    return decision;
                }
            }
            chosen.push_back(num);
            total += num;
        }

        if (skip) {
            // Re-prompt for input
            continue;
        }

        if (chosen.empty())
        {
            // If user typed some non-integer or blank, we end up here
            cout << "No valid squares entered. Please try again.\n";
            continue; // re-prompt
        }

        if (total != diceSum)
        {
            cout << "Invalid input: the numbers you entered sum to " << total
                << ", but they must sum to " << diceSum << ". Please try again.\n";
            // re-prompt without skipping
            continue;
        }

        // If we reach here, sum matches diceSum
        decision.squares = chosen;
        break;
    }

    return decision;
}