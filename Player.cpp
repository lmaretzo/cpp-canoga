/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#include "Player.h"
#include <iostream> // for debugging or printing in hint method

using namespace std;



#include <algorithm>  // for sort, max

// Recursively find all combinations of numbers in 'nums' that sum to 'target'.
// 'start' is the starting index, 'current' holds the current combination.
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

// Given a set of available numbers, return all combinations (of 1 to 4 numbers) that sum to 'target'.
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
Purpose: Initializes a Player object with a name, computer flag, and board size.
Parameters:
    - name: The name of the player.
    - isComp: Boolean flag indicating if the player is AI-controlled.
    - boardSize: The number of squares on the player's board.
Return Value: None
Algorithm:
    1) Assign playerName and computer flag.
    2) Call resetSquares(boardSize) to initialize the board.
Reference: AI assistance (ChatGPT) was used to refine dynamic board size initialization.
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
Purpose: Returns the player's name.
Parameters: None
Return Value: A string representing the player's name.
Reference: None
********************************************************************* */
string Player::getName() const
{
    return playerName;
}

//bool Player::isComputerPlayer() const
//{
//    return computer;
//}

int Player::getScore() const
{
    return score;
}

void Player::setName(const string& name)
{
    playerName = name;
}

//void Player::setIsComputer(bool flag)
//{
//    computer = flag;
//}

void Player::addToScore(int points)
{
    score += points;
}

/* *********************************************************************
Function Name: coverSquare
Purpose: Covers a square on the player's board.
Parameters:
    - squareLabel: The number of the square to cover (1-based index).
Return Value: Boolean indicating whether the operation was successful.
Algorithm:
    1) Validate that squareLabel is within the board range.
    2) Check if the square is already covered.
    3) If uncovered, mark it as covered.
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
Purpose: Uncovers a square on the opponent's board.
Parameters:
    - squareLabel: The number of the square to uncover (1-based index).
Return Value: Boolean indicating whether the operation was successful.
Algorithm:
    1) Validate that squareLabel is within the board range.
    2) Check if the square is already uncovered.
    3) If covered, mark it as uncovered.
Reference: AI assistance (ChatGPT) was used for optimizing board state validation.
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

bool Player::areAllCovered() const
{
    for (int val : squares)
    {
        if (val == 0) return false;
    }
    return true;
}

bool Player::areAllUncovered() const
{
    for (int val : squares)
    {
        if (val != 0) return false;
    }
    return true;
}

vector<int> Player::getSquares() const
{
    return squares; // return a copy
}

/* *********************************************************************
Function Name: printBoard
Purpose: Displays the player's board state in a visually formatted manner.
Parameters: None
Return Value: None
Algorithm:
    1) Print the player's name.
    2) Print a top border dynamically based on board size.
    3) Print each square, showing its number if uncovered, or 'X' if covered.
    4) Print a bottom border.
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
Function Name: chooseSquares
Purpose: Default virtual method for choosing squares based on a dice roll.
         This method implements the default AI strategy.
Parameters:
    - diceSum: The total from the dice roll.
Return Value: A vector of integers representing the chosen squares.
Reference: This is the default AI strategy.
********************************************************************* */


// ---------- New Unified Decision Method ----------
//
// This method implements the default AI strategy for covering moves.
// It returns a MoveDecision structure.
MoveDecision Player::decideMove(int diceSum) {
    // Default strategy for a covering move.
    MoveDecision decision;
    decision.cover = true; // Default to covering
    int boardSize = squares.size();
    vector<int> available;
    for (int i = 0; i < boardSize; i++) {
        if (squares[i] == 0)
            available.push_back(i + 1);
    }
    vector<vector<int>> combos = getCombinations(available, diceSum);
    if (combos.empty()) {
       // cout << "[" << playerName << "] (Default Strategy) No valid covering move found.\n";
        decision.squares = vector<int>(); // empty means no move (skip)
        return decision;
    }
    // Heuristic: choose the combination with the highest maximum element.
    vector<int> best = combos[0];
    int bestMax = 0;
    for (int n : best)
        bestMax = max(bestMax, n);
    for (auto& combo : combos) {
        int currentMax = 0;
        for (int n : combo)
            currentMax = max(currentMax, n);
        if (currentMax > bestMax) {
            best = combo;
            bestMax = currentMax;
        }
    }
    //cout << "[" << playerName << "] (Default Strategy - Cover) Recommended move: ";
    for (int n : best)
    //    cout << n << " ";
    cout << "\n";
    decision.squares = best;
    return decision;
}

void Player::offerHint() {
    cout << "[" << playerName << "] HINT: (Not yet implemented)\n";
}