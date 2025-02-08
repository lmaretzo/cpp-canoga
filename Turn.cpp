#include "Turn.h"
#include "InputValidator.h"
#include <sstream>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <chrono>
#include "Computer.h"   // NEW: Include Computer.h so that the type is known.


using namespace std;

// NEW CODE: Modified constructor to initialize the allowUncover flag.
Turn::Turn(Player& activePlayer, Player& opp, Dice& d, bool allowUncover)
    : player(activePlayer), opponent(opp), diceRef(d), allowUncover(allowUncover),
    lastMoveWasUncover(false)
{
}

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

bool Turn::areSquaresSevenToNCovered(const Player& player) const {
    const vector<int>& squares = player.getSquares();
    for (int i = 6; i < squares.size(); ++i) { // Index 6 = square 7
        if (squares[i] == 0) { // Uncovered square
            return false;
        }
    }
    return true;
}

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

void Turn::execute() {
    cout << "\n--- " << player.getName() << "'s TURN ---\n";
    bool stillRolling = true;
    do {
        player.printBoard();

        // NEW: If the active player is Computer, display "Rolling..." and pause.
            cout << "\nRolling...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2300)); // pause 1 sec
        

        bool allCoveredSevenToN = areSquaresSevenToNCovered(player);
        int diceToRoll = 2;
        if (allCoveredSevenToN) {
            bool rollOneDie = InputValidator::getYesNo(
                "All squares 7 through " + to_string(player.getSquares().size()) +
                " are covered. Do you want to roll one die? (y/n): ");
            diceToRoll = rollOneDie ? 1 : 2;
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
// Use the unified decision method.
        MoveDecision decision = player.decideMove(sum, opponent);
        lastMoveWasUncover = !decision.cover;  // NEW: Set the flag based on the decision.
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
            break;
        }
    } while (stillRolling);
}

// New helper: checks if there is any valid uncover combination on p’s board.
// (Here p will be the opponent.)
bool Turn::canUncoverAnyCombination(const Player& p, int sum) const {
    vector<int> squaresCopy = p.getSquares();
    vector<int> covered;
    // For uncovering, we want to use the squares that are currently covered.
    for (int i = 0; i < (int)squaresCopy.size(); i++) {
        if (squaresCopy[i] != 0)  // note: unlike covering, we check for nonzero!
            covered.push_back(i + 1);
    }
    // Now, check all subsets of these covered squares
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

