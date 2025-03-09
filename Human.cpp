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
         name      - a string representing the human player's name (passed by value)
         boardSize - an integer representing the number of squares on the board
Return Value: None.
Algorithm:
         1) Call the base class (Player) constructor with the provided name and board size.
Reference: None
********************************************************************* */
Human::Human(const string& name, int boardSize, Tournament* tournament)
    : Player(name, boardSize), tournamentPtr(tournament)
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

MoveDecision Human::decideMove(int diceSum, const Player& opponent, bool allowUncover, const Tournament* tournamentPtr) {
    MoveDecision decision;



    // First, ask if the user wants a hint.
    bool wantHint = getYesNo("Would you like a hint for your move? (y/n): ");
    if (wantHint) {
        MoveDecision hintDecision = Player::decideMove(diceSum, opponent, allowUncover, tournamentPtr);
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

    // Now using InputValidator to ask if the user wants to cover.
    // (Yes = cover; No = uncover.)
    bool cover;

    // Check if the opponent has any covered squares
    // Check opponent squares and handicap protection
    bool opponentHasCoveredSquares = false;
    vector<int> oppSquares = opponent.getSquares();
    for (int sq : oppSquares) {
        if (sq != 0) {
            opponentHasCoveredSquares = true;
            break;
        }
    }

	//RIGHT HERE IT IS DECIDING TO COVER OR UNCOVER WHICH IS AFTER THE CALCULCATIONS OF THE OPPONENTS SQUARES WHICH IS WRONG IT NEEDS TO BE BEFORE.
    bool handicapBlocking = tournamentPtr && tournamentPtr->getHandicapActive() &&
        opponent.getName() == tournamentPtr->getAdvantagePlayerName() &&
        !opponent.getHasHadTurnInRound();

    // Force covering in these cases:
    bool forceCovering = false;
    string reasonMessage = "";

    // Use the centralized function to determine if uncovering is allowed
    if (!opponentHasCoveredSquares || handicapBlocking || !canUncover(diceSum, opponent, tournamentPtr)) {
        forceCovering = true;

        // Determine the reason for better user feedback
        //if (!allowUncover) {
        //    reasonMessage = "Uncovering is not allowed on the first turn.";
        //}
        if (!opponentHasCoveredSquares) {
            reasonMessage = "Uncovering is not allowed because the opponent has no covered squares.";
        }
        else if (handicapBlocking) {
            reasonMessage = "Uncovering is not allowed because " + opponent.getName() +
                " has the handicap advantage and hasn't had a turn yet.";
        }
        else {
            reasonMessage = "Uncovering is not allowed because there are no valid combinations that sum to " + std::to_string(diceSum) + ".";
        }
    }



    if (forceCovering) {
        cover = true;
        cout << reasonMessage << " You must cover your own squares." << endl;
    }
    else {
        cover = getYesNo("Do you want to cover your squares? (y for cover, n for uncover): ");
    }
    decision.cover = cover;


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
            continue; // Re-prompt for input
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