#include "Turn.h"
#include "InputValidator.h"
#include <sstream>
#include <iostream>
#include <limits>
#include <string>


using namespace std;

Turn::Turn(Player& activePlayer, Player& opp, Dice& d)
    : player(activePlayer), opponent(opp), diceRef(d)
{
}
/*** NEW CODE START ***/

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
        if (total == sum && count <= 4)
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


void Turn::execute()
{
    // For demonstration: the player does exactly one roll in this Turn.
    // Later, you can extend so the player continues rolling until no valid move is possible.

    cout << "\n--- " << player.getName() << "'s TURN ---\n";

    bool stillRolling = true;
    do
    {
        player.printBoard();




                // NEW CODE: Check if squares 7 through n are covered
        bool allCoveredSevenToN = areSquaresSevenToNCovered(player);
        int diceToRoll = 2; // Default: roll two dice

        if (allCoveredSevenToN) {

            // NEW CODE: Use InputValidator for yes/no question
            bool rollOneDie = InputValidator::getYesNo(
                "All squares 7 through " + to_string(player.getSquares().size()) +
                " are covered. Do you want to roll one die? (y/n): ");

            diceToRoll = rollOneDie ? 1 : 2; // Set diceToRoll based on user's choice
        }
        else {
            cout << "Squares 7 through " << player.getSquares().size()
                << " are not all covered. You must roll two dice.\n";
        }


        pair<int, int> rollVal = diceRef.roll(diceToRoll); // Use the Dice class's roll method



        int sum = rollVal.first + rollVal.second;


        cout << player.getName() << " rolled "
            << rollVal.first << " and " << rollVal.second
            << " (sum = " << sum << ")\n";

        if (sum == 0) {
            // NEW CODE: Handle turn skip
            cout << player.getName() << " chose to skip their turn.\n";
            break;
        }


        // 2) Check if covering is even possible
        if (!canCoverAnyCombination(player, sum))
        {
            cout << "No valid moves for sum = " << sum
                << ". " << player.getName() << "'s turn ends.\n";
            break;
        }

        // 3) Attempt to cover squares
        bool success = coverSquares(sum);
        if (!success)
        {
            cout << player.getName()
                << " did not cover squares. Turn ends.\n";
            break;
        }

        // 4) Check if player has covered all squares
        if (player.areAllCovered())
        {
            cout << player.getName()
                << " has covered all squares!\n";
            break;  // Round logic can handle the actual 'win' 
        }

        // If we reach here, it means we covered squares successfully
        // and can roll again. If you want to let the user decide to stop,
        // you can ask them. For now, we automatically continue rolling.
    } while (stillRolling);
    /*** NEW CODE END ***/
}


// Very naive approach: we'll just ask the user for squares to cover that sum up to diceSum
bool Turn::coverSquares(int diceSum)
{
    cout << player.getName() << ", enter the squares you want to cover (space-separated), sum must be "
        << diceSum << ". Enter 0 to skip.\n";

    // We'll read a line of input, parse integers, and see if they sum to diceSum.
    // For simplicity, let the user do the sum. If it equals diceSum, we attempt to cover them.
    // If covering fails (some squares already covered, etc.), we revert.

    vector<int> chosen;
    while (true)
    {
        chosen.clear();

        cout << "Squares to cover (e.g. '1 2' or '3' or '0' to skip): ";

        // cin.ignore(numeric_limits<streamsize>::max(), '\n');


        string line;
        getline(cin, line);

        cout << "[DEBUG] Raw input: " << line << "\n"; //debug statement 1/26 5:00pm


        if (line.empty())
        {
            // if the getline is empty (maybe leftover from a previous input?), read again
            continue;
        }

        // parse
        int val;
        bool skip = false;
        bool validParse = true;
        int sumCheck = 0;

        // use a stringstream
        std::stringstream ss(line);

        while (ss >> val)
        {
            if (val == 0) {
                // NEW CODE: Handle skipping the turn
                cout << player.getName() << " chose to skip their turn.\n";
                return false;
            }
            if (val < 1 || val > player.getSquares().size())
            {
                validParse = false;
                break;
            }
            if (std::find(chosen.begin(), chosen.end(), val) != chosen.end()) {
                // Duplicate value detected
                cout << "You cannot use the same square twice. ";
                validParse = false; // Mark the input as invalid
                break;
            }


            chosen.push_back(val);
            sumCheck += val;

            // NEW CODE: Prevent selecting more than 4 squares
            if (chosen.size() > 4)
            {
                cout << "You can only choose up to 4 squares. Try again.\n";
                validParse = false;
                break;
            }
        }

        if (!validParse || sumCheck != diceSum) // NEW: Now allows 4 squares)
        {
            cout << "Invalid selection. Make sure the numbers sum to " << diceSum << " and you only pick up to 4 squares.\n";
            continue;
        }

        if (skip)
        {
            // user chose to skip
            return false;
        }

        if (sumCheck == diceSum)
        {
            // Attempt covering
            bool allCovered = true;
            for (int sq : chosen)
            {
                bool c = player.coverSquare(sq);
                if (!c)
                {
                    // revert
                    allCovered = false;
                    for (int revertSq : chosen)
                    {
                        // only uncover if it was successfully covered
                        // (this ensures partial covers don't remain)
                        player.uncoverSquare(revertSq);
                    }
                    cout << "Could not cover squares. Try again.\n";
                    break;
                }
            }

            if (allCovered)
            {
                cout << "Covered squares: ";
                for (int sq : chosen) cout << sq << " ";
                cout << "\n";
                return true;
            }
        }
        else
        {
            cout << "Squares do not sum to " << diceSum << ". Try again.\n";
        }
    }

    // Should never really get here in normal flow
    return false;
}