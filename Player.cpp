/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#include "Player.h"
#include <iostream> // for debugging or printing in hint method

using namespace std;



#include <algorithm>  // for sort, max

/* *********************************************************************
Function Name: findCombinations
Purpose: To recursively find all combinations of numbers in 'nums' that sum
         to 'target'. Only combinations containing between 1 and 4 numbers are considered.
Parameters:
         nums    - a constant reference to a vector of integers (available numbers)
         target  - an integer representing the desired sum
         start   - an integer index from where to start considering numbers in 'nums'
         current - a reference to a vector of integers holding the current combination
         result  - a reference to a vector of vectors, where valid combinations are stored
Return Value: None.
Algorithm:
         1) If target is 0 and current combination size is between 1 and 4, add it to result.
         2) If current combination size is 4, return without further recursion.
         3) Iterate over nums starting from 'start'; for each number less than or equal to target,
            add it to current, recursively call findCombinations with updated target and start,
            then remove the number from current.
Reference: None
********************************************************************* */
void findCombinations(const vector<int>& nums, int target, int start,
    vector<int>& current, vector<vector<int>>& result) {
    if (target == 0 && current.size() >= 1 && current.size() <= 4) {
        result.push_back(current);
    }
    if (current.size() == 4) return; // cannot choose more than 4 squares
    for (int i = start; i < nums.size(); i++) {
        if (nums[i] > target)
            continue;  // skip numbers that are too large
        current.push_back(nums[i]);
        findCombinations(nums, target - nums[i], i + 1, current, result);
        current.pop_back();
    }
}

/* *********************************************************************
Function Name: getCombinations
Purpose: To obtain all valid combinations of numbers from the available set that
         sum up to the target value.
Parameters:
         available - a constant reference to a vector of integers representing the available numbers
         target    - an integer representing the desired sum
Return Value: A vector of vectors of integers, each inner vector is a valid combination.
Algorithm:
         1) Make a copy of available numbers and sort them.
         2) Use findCombinations to compute all valid combinations.
         3) Return the computed combinations.
Reference: None
********************************************************************* */
vector<vector<int>> getCombinations(const vector<int>& available, int target) {
    vector<int> nums = available;
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> current;
    findCombinations(nums, target, 0, current, result);
    return result;
}


/* *********************************************************************
Function Name: Player (Default Constructor)
Purpose: Initializes a Player object with default values.
Parameters: None
Return Value: None
Algorithm:
    1) Initialize playerName to "Unknown".
    2) Set computer flag to false.
    3) Initialize score to 0.
    4) Create a vector of 9 squares, all uncovered (set to 0).
Reference: None 
********************************************************************* */
Player::Player()
    : playerName("Unknown"), score(0), squares(9, 0)
{
    // squares default to uncovered (all zero).
}

/* *********************************************************************
Function Name: Player (Parameterized Constructor)
Purpose: To initialize a Player object with a specified name and board size.
Parameters:
         name      - a string representing the player's name (passed by value)
         boardSize - an integer representing the number of squares on the board
Return Value: None.
Algorithm:
         1) Set playerName to the given name and score to 0.
         2) Call resetSquares(boardSize) to initialize the board.
Reference: AI ASSISTED
********************************************************************* */
Player::Player(const string& name, int boardSize)
    : playerName(name), score(0)
{
        resetSquares(boardSize);
}

/* *********************************************************************
Function Name: resetSquares
Purpose: Resets the player's board to the specified size with all squares uncovered.
Parameters:
    - boardSize: The number of squares on the player's board.
Return Value: None
Algorithm:
    1) Assign a vector of size boardSize with all values set to 0.
Reference: None
********************************************************************* */
void Player::resetSquares(int boardSize)
{
    squares.assign(boardSize, 0); // Reset squares dynamically based on the board size
}

Player::~Player()
{
    // nothing special
}

/* *********************************************************************
Function Name: getName
Purpose: To retrieve the player's name.
Parameters: None.
Return Value: A string representing the player's name.
Algorithm:
         1) Return the value of playerName.
Reference: None
********************************************************************* */
string Player::getName() const
{
    return playerName;
}

/* *********************************************************************
Function Name: getScore
Purpose: To retrieve the player's current score.
Parameters: None.
Return Value: An integer representing the player's score.
Algorithm:
         1) Return the value of score.
Reference: None
********************************************************************* */

int Player::getScore() const
{
    return score;
}

/* *********************************************************************
Function Name: setName
Purpose: To update the player's name.
Parameters:
         name - a string representing the new player name (passed by value)
Return Value: None.
Algorithm:
         1) Set the playerName attribute to the provided name.
Reference: None
********************************************************************* */
void Player::setName(const string& name)
{
    playerName = name;
}

/* *********************************************************************
Function Name: addToScore
Purpose: To add points to the player's score.
Parameters:
         points - an integer representing the points to add
Return Value: None.
Algorithm:
         1) Increment score by the provided points.
Reference: None
********************************************************************* */

void Player::addToScore(int points)
{
    score += points;
}

/* *********************************************************************
Function Name: coverSquare
Purpose: To cover a specific square on the player's board.
Parameters:
         squareLabel - an integer (1-based index) representing the square to cover
Return Value: A boolean value; true if the square was successfully covered, false otherwise.
Algorithm:
         1) Check if squareLabel is within range.
         2) If the square is already covered (non-zero), return false.
         3) Otherwise, set the square's value to its label and return true.
Reference: None
********************************************************************* */
bool Player::coverSquare(int squareLabel)
{
    if (squareLabel < 1 || squareLabel > squares.size()) return false;
    int idx = squareLabel - 1;
    if (squares[idx] != 0)
    {
        // already covered
        return false;
    }
    squares[idx] = squareLabel; // now covered
    return true;
}

/* *********************************************************************
Function Name: uncoverSquare
Purpose: To uncover a specific square on the player's board.
Parameters:
         squareLabel - an integer (1-based index) representing the square to uncover
Return Value: A boolean value; true if the square was successfully uncovered, false otherwise.
Algorithm:
         1) Check if squareLabel is within range.
         2) If the square is already uncovered (0), return false.
         3) Otherwise, set the square's value to 0 (uncover it) and return true.
Reference: AI ASSISTED
********************************************************************* */
bool Player::uncoverSquare(int squareLabel)
{
    if (squareLabel < 1 || squareLabel > squares.size()) return false;
    int idx = squareLabel - 1;
    if (squares[idx] == 0)
    {
        // already uncovered
        return false;
    }
    squares[idx] = 0; // now uncovered
    return true;
}

/* *********************************************************************
Function Name: areAllCovered
Purpose: To check if all squares on the board are covered.
Parameters: None.
Return Value: A boolean value; true if all squares are covered, false otherwise.
Algorithm:
         1) Iterate over the squares vector.
         2) If any square is 0 (uncovered), return false.
         3) If none are uncovered, return true.
Reference: None
********************************************************************* */
bool Player::areAllCovered() const
{
    for (int val : squares)
    {
        if (val == 0) return false;
    }
    return true;
}


/* *********************************************************************
Function Name: areAllUncovered
Purpose: To check if all squares on the board are uncovered.
Parameters: None.
Return Value: A boolean value; true if all squares are uncovered, false otherwise.
Algorithm:
         1) Iterate over the squares vector.
         2) If any square is non-zero (covered), return false.
         3) If all squares are 0, return true.
Reference: None
********************************************************************* */
bool Player::areAllUncovered() const
{
    for (int val : squares)
    {
        if (val != 0) return false;
    }
    return true;
}

/* *********************************************************************
Function Name: getSquares
Purpose: To return a copy of the player's board.
Parameters: None.
Return Value: A vector of integers representing the board.
Algorithm:
         1) Return a copy of the squares vector.
Reference: None
********************************************************************* */
vector<int> Player::getSquares() const
{
    return squares; // return a copy
}

/* *********************************************************************
Function Name: printBoard
Purpose: To display the player's board in a formatted manner.
Parameters: None.
Return Value: None.
Algorithm:
         1) Print the player's name.
         2) Dynamically generate a top border.
         3) Print each square's content (number if uncovered, "X" if covered).
         4) Dynamically generate a bottom border.
Reference: None
********************************************************************* */
void Player::printBoard() const {
    cout << endl;
    cout << playerName << "'s Board:" << endl;

    // Generate the top border dynamically
    for (int i = 0; i < squares.size(); ++i) {
        cout << "+---";
    }
    cout << "+" << endl; // End the top border

    // Generate the row content dynamically
    for (int i = 0; i < squares.size(); ++i) {
        if (squares[i] == 0) {
            // Uncovered square shows its number
            if (i + 1 < 10) {
                cout << "| " << (i + 1) << " "; // Single-digit alignment
            }
            else {
                cout << "| " << (i + 1); // Double-digit alignment
            }
        }
        else {
            // Covered square shows "X"
            cout << "| X ";
        }
    }
    cout << "|" << endl; // End the row content

    // Generate the bottom border dynamically
    for (int i = 0; i < squares.size(); ++i) {
        cout << "+---";
    }
    cout << "+" << endl; // End the bottom border

    cout << endl;
}


/* *********************************************************************
Function Name: decideMove
Purpose: To determine the move for the player based on the dice roll and
         the state of the opponent's board. This default AI strategy computes
         valid cover and uncover combinations and chooses one based on a simple
         heuristic.
Parameters:
         diceSum      - an integer representing the total of the dice roll
         opponent     - a constant reference to the opponent Player object
         allowUncover - a boolean flag indicating whether uncovering is allowed this turn
Return Value: A MoveDecision structure containing the chosen move (cover/uncover)
              and the list of squares.
Algorithm:
         1) For covering: Gather all uncovered squares from the player's board.
         2) Compute all valid combinations (1 to 4 numbers) that sum to diceSum.
         3) Choose the combination with the highest maximum value as the cover move.
         4) For uncovering: Gather all covered squares from the opponent's board.
         5) Compute all valid combinations that sum to diceSum.
         6) Choose the combination with the lowest total as the uncover move.
         7) Compare both moves; if both are valid, choose the one with the lower total (heuristic).
         8) Return the corresponding MoveDecision.
Reference: AI ASSISTED
********************************************************************* */
MoveDecision Player::decideMove(int diceSum, const Player& opponent, bool allowUncover) {
    MoveDecision coverDecision, uncoverDecision;
    coverDecision.cover = true;   // default for covering
    uncoverDecision.cover = false; // default for uncovering

    // --- Compute Cover Decision ---
    vector<int> myAvailable;
    for (int i = 0; i < static_cast<int>(squares.size()); i++) {
        if (squares[i] == 0)
            myAvailable.push_back(i + 1);
    }
    vector<vector<int>> coverCombos = getCombinations(myAvailable, diceSum);
    if (!coverCombos.empty()) {
        coverDecision.squares = coverCombos[0];
        int bestMax = 0;
        for (int n : coverDecision.squares)
            bestMax = max(bestMax, n);
        for (auto& combo : coverCombos) {
            int currentMax = 0;
            for (int n : combo)
                currentMax = max(currentMax, n);
            if (currentMax > bestMax) {
                coverDecision.squares = combo;
                bestMax = currentMax;
            }
        }
    }
    else {
        coverDecision.squares.clear();
    }

    // --- Compute Uncover Decision ---
    vector<int> oppCovered;
    vector<int> oppSquares = opponent.getSquares();
    for (int i = 0; i < static_cast<int>(oppSquares.size()); i++) {
        if (oppSquares[i] != 0)  // if the opponent's square is covered
            oppCovered.push_back(i + 1);
    }
    vector<vector<int>> uncoverCombos = getCombinations(oppCovered, diceSum);
    if (!uncoverCombos.empty()) {
        uncoverDecision.squares = uncoverCombos[0];
        int bestTotal = 0;
        for (int n : uncoverDecision.squares)
            bestTotal += n;
        for (auto& combo : uncoverCombos) {
            int comboTotal = 0;
            for (int n : combo)
                comboTotal += n;
            if (comboTotal < bestTotal) {
                uncoverDecision.squares = combo;
                bestTotal = comboTotal;
            }
        }
    }
    else {
        uncoverDecision.squares.clear();
    }

    // --- Debug Output ---
    cout << "[" << playerName << "] Computed Cover Move: ";
    if (!coverDecision.squares.empty()) {
        for (int n : coverDecision.squares)
            cout << n << " ";
    }
    else {
        cout << "None";
    }
    cout << "\n";

    cout << "[" << playerName << "] Computed Uncover Move: ";
    if (!uncoverDecision.squares.empty()) {
        for (int n : uncoverDecision.squares)
            cout << n << " ";
    }
    else {
        cout << "None";
    }
    cout << "\n";

    // --- Choose Between Cover and Uncover ---
    // Use a simple heuristic: compare the total values of the moves.
    if (!coverDecision.squares.empty() && !uncoverDecision.squares.empty()) {
        int coverTotal = 0, uncoverTotal = 0;
        for (int n : coverDecision.squares)
            coverTotal += n;
        for (int n : uncoverDecision.squares)
            uncoverTotal += n;
        // For example, choose to uncover if its total is lower than the cover move’s total.
        if (uncoverTotal < coverTotal)
            return uncoverDecision;
        else
            return coverDecision;
    }
    else if (!uncoverDecision.squares.empty()) {
        return uncoverDecision;
    }
    else {
        return coverDecision;
    }
}


/* *********************************************************************
Function Name: offerHint
Purpose: To provide a hint for the player's move. (Placeholder function.)
Parameters: None.
Return Value: None.
Algorithm:
         1) Print a message indicating that hint functionality is not yet implemented.
Reference: None
********************************************************************* */
void Player::offerHint() {
    cout << "[" << playerName << "] HINT: (Not yet implemented)\n";
}