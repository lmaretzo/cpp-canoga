/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/
#include "Turn.h"
#include "InputValidator.h"
#include <sstream>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <chrono>
#include "Computer.h"   // Include Computer.h so that the type is known.
#include "Tournament.h"

using namespace std;

/* *********************************************************************
Function Name: Turn (Constructor)
Purpose: To initialize a Turn object with the active player, the opponent,
         a reference to the dice object, and a flag indicating whether
         uncovering is allowed this turn.
Parameters:
         activePlayer - a reference to the Player taking this turn (by reference)
         opp          - a reference to the opponent Player object (by reference)
         d            - a reference to the Dice object (by reference)
         allowUncover - a boolean flag that is true if uncovering is allowed, false otherwise
Return Value: None.
Algorithm:
         1) Initialize member variables with the given parameters.
         2) Set lastMoveWasUncover to false.
Reference: None
********************************************************************* */
Turn::Turn(Player& activePlayer, Player& opp, Dice& d, bool allowUncover, Tournament* tPtr)
    : player(activePlayer), opponent(opp), diceRef(d), allowUncover(allowUncover),
    lastMoveWasUncover(false), tournamentPtr(tPtr)
{

}

/* *********************************************************************
Function Name: canCoverAnyCombination
Purpose: To check whether there is any valid combination of uncovered squares
         on the given player's board that sum to the provided dice sum.
Parameters:
         p   - a constant reference to the Player whose board is checked
         sum - an integer representing the dice sum
Return Value: A boolean value; true if at least one valid combination exists, false otherwise.
Algorithm:
         1) Retrieve the player's squares.
         2) Build a vector of numbers representing uncovered squares.
         3) Iterate through all subsets of these numbers to check if any subset sums to 'sum'.
Reference: AI ASSISTED
********************************************************************* */
bool Turn::canCoverAnyCombination(const Player& p, int sum) const
{
    vector<int> squaresCopy = p.getSquares();
    vector<int> uncovered;
    for (int i = 0; i < (int)squaresCopy.size(); i++)
    {
        if (squaresCopy[i] == 0)
            uncovered.push_back(i + 1);
    }

    // Check all subsets of uncovered squares
    int subsetCount = (1 << uncovered.size());
    for (int mask = 1; mask < subsetCount; mask++)
    {
        int total = 0, count = 0;
        for (size_t bit = 0; bit < uncovered.size(); bit++)
        {
            if (mask & (1 << bit))
            {
                total += uncovered[bit];
                count++;
            }
        }
        if (total == sum && count >= 1 && count <= 4)
            return true; // Found a valid combo
    }
    return false;
}


/* *********************************************************************
Function Name: areSquaresSevenToNCovered
Purpose: To determine if squares numbered 7 through N on the player's board
         are all covered.
Parameters:
         player - a constant reference to the Player whose board is checked
Return Value: A boolean value; true if all squares from 7 to N are covered, false otherwise.
Algorithm:
         1) Retrieve the player's squares.
         2) Starting from index 6 (square 7), check if any square is uncovered (value 0).
         3) If any such square is found, return false; otherwise, return true.
Reference: None
********************************************************************* */
bool Turn::areSquaresSevenToNCovered(const Player& player) const {
    const vector<int>& squares = player.getSquares();
    for (int i = 6; i < squares.size(); ++i) { // Index 6 = square 7
        if (squares[i] == 0) { // Uncovered square
            return false;
        }
    }
    return true;
}

/* *********************************************************************
Function Name: printDice
Purpose: To display the dice roll visually using ASCII art.
Parameters:
         d1        - an integer representing the value of the first die
         d2        - an integer representing the value of the second die
         diceCount - an integer indicating the number of dice rolled (1 or 2)
Return Value: None.
Algorithm:
         1) If one die is rolled, print a single dice box.
         2) If two dice are rolled, print two dice boxes side by side.
Reference: None
********************************************************************* */
void printDice(int d1, int d2, int diceCount) {
    if (diceCount == 1) {
        cout << "+-----+\n";
        cout << "|  " << d1 << "  |\n";
        cout << "+-----+\n";
    }
    else { // diceCount == 2
        cout << "+-----+ " << "+-----+\n";
        cout << "|  " << d1 << "  | " << "|  " << d2 << "  |\n";
        cout << "+-----+ " << "+-----+\n";
    }
}

/* *********************************************************************
Function Name: execute
Purpose: To execute a single turn for the active player. This function:
         - Displays the board.
         - Rolls the dice (or prompts if necessary).
         - Checks for valid moves.
         - Calls the player's decideMove method.
         - Applies the chosen move.
         - Checks for win conditions.
Parameters: None.
Return Value: None.
Algorithm:
         1) Print the active player's board.
         2) Pause and display a rolling message.
         3) Determine if squares 7 to N are covered and decide whether to roll one or two dice.
         4) Roll the dice and compute the sum.
         5) If no valid move exists, end the turn.
         6) Retrieve the move decision from the active player.
         7) Apply the move to the appropriate board.
         8) If the move cannot be applied, end the turn.
         9) Print the applied move and check for immediate win conditions.
Reference: AI ASSISTED
********************************************************************* */
void Turn::execute() {
    cout << "Debug: At start of execute(), player = " << player.getName() << endl;

    cout << "\n--- " << player.getName() << "'s TURN ---\n";
    bool stillRolling = true;
    bool roundEnded = false;  // track if the player ended the round

    do {
        player.printBoard();

        // If the active player is Computer, display "Rolling..." and pause.
        cout << "\nRolling...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // pause for sec

        bool allCoveredSevenToN = areSquaresSevenToNCovered(player);
        int diceToRoll = 2;  // Default: roll two dice.
        if (allCoveredSevenToN) {
            // Compute the optimal dice roll using the new function in the Player class.
            int optimal = player.optimalDiceRoll();
            if (player.getName() == "Computer") {
                // For computer players, automatically use the optimal dice roll.
                diceToRoll = optimal;
            }
            else {
                // For human players, first ask if they want a hint regarding the optimal dice roll.
                bool wantHint = getYesNo("Would you like a hint for the optimal dice roll? (y/n): ");
                if (wantHint) {
                    // Display the hint.
                    cout << "Hint: Based on your board, the optimal dice roll is "
                        << optimal << " die" << (optimal == 1 ? "" : "s") << ".\n";
                }
                // Then prompt the user to choose whether to roll one die.
                bool rollOneDie = getYesNo("Do you want to roll one die? (y/n): ");
                diceToRoll = rollOneDie ? 1 : 2;
            }
        }


        pair<int, int> rollVal = diceRef.roll(diceToRoll);
        int sum = rollVal.first + rollVal.second;
        printDice(rollVal.first, rollVal.second, diceToRoll);
        cout << "Sum = " << sum << "\n" << "\n";

        if (sum == 0) {
            cout << player.getName() << " chose to skip their turn.\n";
            break;
        }
        if (!(canCoverAnyCombination(player, sum) || canUncoverAnyCombination(opponent, sum))) {
            cout << "No valid moves for sum = " << sum << ". "
                << player.getName() << "'s turn ends.\n";
            break;
        }

        // Use the unified decision method.
        MoveDecision decision;
        cout << "Debug: Before decideMove(), player = " << player.getName() << endl;
        cout << "Debug: player is of type " << typeid(player).name() << endl;
        if (dynamic_cast<Computer*>(&player)) {
            cout << player.getName() << " (AI) is making a move...\n";
            decision = static_cast<Computer*>(&player)->decideMove(sum, opponent, allowUncover);
        }
        else {
            decision = player.decideMove(sum, opponent, allowUncover);
        }
        lastMoveWasUncover = !decision.cover;  // Set the flag based on the decision.
        if (decision.squares.empty()) {
            cout << player.getName() << " did not choose any squares. Turn ends.\n";
            break;
        }
        bool allSuccessful = true;
        for (int sq : decision.squares) {
            bool success;
            if (decision.cover)
                success = player.coverSquare(sq);
            else
                success = opponent.uncoverSquare(sq);
            if (!success) {
                allSuccessful = false;
                break;
            }
        }
        if (!allSuccessful) {
            cout << "Could not apply the chosen move. Turn ends.\n";
            break;
        }
        cout << (decision.cover ? "Covered" : "Uncovered") << " squares: ";
        for (int sq : decision.squares)
            cout << sq << " ";
        cout << "\n";
        // Immediately end the turn if the opponent is all uncovered
        if (lastMoveWasUncover && opponent.areAllUncovered()) {
            cout << player.getName() << " has uncovered all of "
                << opponent.getName() << "'s squares and wins the round!\n";
            return; // End turn immediately
        }
        if (!decision.cover) {
            cout << "\nUpdated Opponent's Board:\n";
            opponent.printBoard();
        }
        if (allowUncover && lastMoveWasUncover && opponent.areAllUncovered()) {
            cout << player.getName() << " has uncovered all of " << opponent.getName() << "'s squares!\n";
            break;
        }
        if (player.areAllCovered()) {
            cout << player.getName() << " has covered all squares!\n";
            roundEnded = true;

            break;
        }
    } while (stillRolling);
    if (tournamentPtr != nullptr)
    {
        // The opponent is now up next (unless the round is over).
        // So if opponent is "Human", the next turn is "Human"; otherwise "Computer".
        if (opponent.getName() == "Human")
            tournamentPtr->setNextTurn("Human");
        else
            tournamentPtr->setNextTurn("Computer");
    }
    // Only ask to save if:
    // (1) It's the human, AND
    // (2) The round did NOT just end on this turn.
    if (!roundEnded && player.getName() == "Human") {
        if (getYesNo("Would you like to save and quit? (y/n): ")) {
            std::string filename;
            cout << R"(Enter file path with filename ex: C:\Users\savedGame.txt to save game: )";
            cin >> filename;

            if (tournamentPtr != nullptr && tournamentPtr->saveGame(filename)) {
                cout << "Game saved successfully. Exiting...\n";
                exit(0);
            }
            else {
                cout << "Error saving game. Resuming turn/game...\n";
            }
        }
    }

}

/* *********************************************************************
Function Name: canUncoverAnyCombination
Purpose: To check whether there is any valid combination of covered squares
         on the given player's board that sum to the provided dice sum (for uncovering).
Parameters:
         p   - a constant reference to the Player whose board is checked (the opponent)
         sum - an integer representing the dice sum
Return Value: A boolean value; true if at least one valid combination exists, false otherwise.
Algorithm:
         1) Retrieve the board from the player.
         2) Build a vector of numbers representing the covered squares.
         3) Check every subset of these numbers to see if any sum to 'sum'.
Reference: None
********************************************************************* */
bool Turn::canUncoverAnyCombination(const Player& p, int sum) const {
    vector<int> squaresCopy = p.getSquares();
    vector<int> covered;
    // For uncovering, use the squares that are currently covered.
    for (int i = 0; i < (int)squaresCopy.size(); i++) {
        if (squaresCopy[i] != 0)  // unlike covering, check for nonzero
            covered.push_back(i + 1);
    }
    // check all subsets of these covered squares
    int subsetCount = (1 << covered.size());
    for (int mask = 1; mask < subsetCount; mask++) {
        int total = 0, count = 0;
        for (size_t bit = 0; bit < covered.size(); bit++) {
            if (mask & (1 << bit)) {
                total += covered[bit];
                count++;
            }
        }
        if (total == sum && count >= 1 && count <= 4)
            return true; // Found a valid uncover combo
    }
    return false;
}
