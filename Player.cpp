/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#include "Player.h"
#include <iostream> // for debugging or printing in hint method
#include <algorithm>
#include "Tournament.h"

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
void Player::findCombinations(const vector<int>& nums, int target, int start,
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
vector<vector<int>> Player::getCombinations(const vector<int>& available, int target) {
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
    : playerName("Unknown"), score(0), squares(9, 0), hasHadTurnInRound(false)

{
    // squares default to uncovered (all zero).
    boardModified = false;  // NEW: Initialize boardModified in the default constructor.
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
    : playerName(name), score(0), hasHadTurnInRound(false)

{
        resetSquares(boardSize);
        boardModified = false; // Ensure board is marked unmodified.
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
    boardModified = false; // Mark the board as unmodified.
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

//comment later
bool Player::isBoardModified() const {
    return boardModified;
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
    boardModified = true; // Mark the board as modified.
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
bool Player::uncoverSquare(int squareLabel, const Tournament* tournamentPtr)
{
    if (squareLabel < 1 || squareLabel > squares.size()) return false;
    int idx = squareLabel - 1;
    if (squares[idx] == 0)
    {
        // already uncovered
        return false;
    }
    squares[idx] = 0; // now uncovered
    boardModified = true; // Mark the board as modified.
    return true;
}


/* *********************************************************************
Function Name: canUncover
Purpose: Determines if uncovering opponent squares is allowed based on
         game state, available combinations, and handicap rules.
Parameters:
         diceSum       - an integer representing the dice roll sum
         opponent      - a reference to the opponent player
         allowUncover  - a boolean indicating if uncovering is allowed by game rules
         tournamentPtr - a pointer to the Tournament for handicap information
Return Value: A boolean value; true if uncovering is allowed, false otherwise.
Algorithm:
         1) Check if uncovering is allowed by game rules (first turn)
         2) Check if opponent has any covered squares
         3) Check for valid uncover combinations
         4) Check handicap protection
Reference: None
********************************************************************* */
bool Player::canUncover(int diceSum, const Player& opponent, const Tournament* tournamentPtr) const {
    // Rule 1: If opponent has no covered squares, cannot uncover
    bool opponentHasCoveredSquares = false;
    vector<int> oppSquares = opponent.getSquares();
    for (int sq : oppSquares) {
        if (sq != 0) { // Opponent has covered at least one square
            opponentHasCoveredSquares = true;
            break;
        }
    }
    if (!opponentHasCoveredSquares) {
        return false;
    }

    // Rule 2: Handicap protection
    if (tournamentPtr && tournamentPtr->getHandicapActive() &&
        opponent.getName() == tournamentPtr->getAdvantagePlayerName() &&
        !opponent.getHasHadTurnInRound()) {
        return false;
    }

    // Rule 3: Check if there are valid combinations to uncover
    vector<int> oppCovered;
    for (int i = 0; i < static_cast<int>(oppSquares.size()); i++) {
        if (oppSquares[i] != 0)  // Only consider covered squares
            oppCovered.push_back(i + 1);
    }
    vector<vector<int>> uncoverCombos = getCombinations(oppCovered, diceSum);
    if (uncoverCombos.empty()) {
        return false;
    }

    // If we passed all checks, uncovering is allowed
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
Function Name: setSquares
Purpose: To update the player's board state and track modifications.
Parameters:
    - newSquares: A vector of integers representing the new board state.
Return Value: None.
Algorithm:
    1) Assign newSquares to the player's squares vector.
    2) Check if any square is covered (nonzero), and set boardModified accordingly.
Reference: None
********************************************************************* */

void Player::setSquares(const std::vector<int>& newSquares) {
    squares = newSquares;
    // Check if any square is nonzero; if so, mark boardModified as true.
    bool modified = false;
    for (int s : newSquares) {
        if (s != 0) {
            modified = true;
            break;
        }
    }
    boardModified = modified;
}

/* *********************************************************************
Function Name: setScore
Purpose: To update the player's score.
Parameters:
    - newScore: An integer representing the new score.
Return Value: None.
Algorithm:
    1) Assign the provided value to the score variable.
Reference: None
********************************************************************* */

void Player::setScore(int newScore) {
    score = newScore;
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

int Player::optimalDiceRoll() const {
    int countUncovered = 0;
    int totalValue = 0;
    // Iterate over the first six squares (or the full board if it has fewer than six squares).
    for (int i = 0; i < 6 && i < squares.size(); i++) {
        if (squares[i] == 0) { // Uncovered square.
            countUncovered++;
            totalValue += (i + 1); // Use square label (i+1) as its value.
        }
    }
    // If no squares are uncovered, default to one die.
    if (countUncovered == 0)
        return 1;

    double average = static_cast<double>(totalValue) / countUncovered;
    // Example heuristic: If the average uncovered value is high or very few squares remain uncovered, choose one die.
    if (average > 4.0 || countUncovered <= 2)
        return 1;
    else
        return 2;
}




/* *********************************************************************
Function Name: setHasHadTurnInRound
Purpose: Sets the flag indicating whether the player has had a turn in the current round.
Parameters:
         value - a boolean value (true if player has had a turn, false otherwise)
Return Value: None.
Algorithm:
         1) Set the hasHadTurnInRound attribute to the provided value.
Reference: None
********************************************************************* */
void Player::setHasHadTurnInRound(bool value) {
    hasHadTurnInRound = value;
}

/* *********************************************************************
Function Name: getHasHadTurnInRound
Purpose: Gets the flag indicating whether the player has had a turn in the current round.
Parameters: None.
Return Value: A boolean value (true if player has had a turn, false otherwise).
Algorithm:
         1) Return the value of hasHadTurnInRound.
Reference: None
********************************************************************* */
bool Player::getHasHadTurnInRound() const {
    return hasHadTurnInRound;
}

/* *********************************************************************
Function Name: canUncoverSquare
Purpose: Checks if a specific square on the player's board can be uncovered,
         considering handicap protection rules.
Parameters:
         squareLabel - an integer (1-based index) representing the square to check
         tournamentPtr - a pointer to the Tournament object for handicap info
Return Value: A boolean value; true if the square can be uncovered, false otherwise.
Algorithm:
         1) Check if the square is out of range or already uncovered.
         2) Check if the square is protected by handicap rules.
         3) Return true only if the square is covered and not protected.
Reference: None
********************************************************************* */
bool Player::canUncoverSquare(int squareLabel, const Tournament* tournamentPtr) const {
    // Basic validation - square must be in range and covered
    if (squareLabel < 1 || squareLabel > squares.size()) return false;
    int idx = squareLabel - 1;
    if (squares[idx] == 0) return false;  // Already uncovered

    // If no tournament pointer or handicap isn't active, no additional restrictions
    if (!tournamentPtr || !tournamentPtr->getHandicapActive()) return true;

    // Check if this is a handicap square
    if (squareLabel == tournamentPtr->getHandicapSquare() &&
        getName() == tournamentPtr->getAdvantagePlayerName() &&
        !hasHadTurnInRound) {
        // This is the handicap square for the advantage player who hasn't had a turn yet
        return false;  // Cannot uncover this protected square
    }

    return true;  // Square can be uncovered
}

/* *********************************************************************
Function Name: decideMove
Purpose: To determine the player's move based on the dice roll and the state
         of the opponent's board using an advanced heuristic.
         This method computes valid combinations for both covering and uncovering,
         scores each candidate move, and returns a MoveDecision along with an explanation.
Parameters:
         diceSum      - an integer representing the total from the dice roll
         opponent     - a constant reference to the opponent Player object
         allowUncover - a boolean flag indicating whether uncovering is allowed this turn
Return Value: A MoveDecision structure containing the chosen move (cover/uncover),
              the list of squares, and a textual explanation of the reasoning.
Algorithm:
         1) Generate candidate moves for covering and uncovering.
         2) If both moves are available, compute:
              - coverScore = (sum of cover candidate) + 2 * (maximum cover candidate value)
              - uncoverScore = (sum of uncover candidate)
         3) If uncoverScore is lower than coverScore, choose uncover; otherwise, choose cover.
         4) Generate detailed explanations for each square in the chosen combination.
         5) If only one type of move is available, return it with square-by-square explanations.
Reference: AI Assisted
********************************************************************* */
MoveDecision Player::decideMove(int diceSum, const Player& opponent, bool allowUncover) {
    MoveDecision coverDecision, uncoverDecision;
    coverDecision.cover = true;   // default for covering
    uncoverDecision.cover = false; // default for uncovering

    // Compute Cover Decision
    vector<int> myAvailable;
    for (int i = 0; i < static_cast<int>(squares.size()); i++) {
        if (squares[i] == 0)
            myAvailable.push_back(i + 1);
    }
    vector<vector<int>> coverCombos = Player::getCombinations(myAvailable, diceSum);
    if (!coverCombos.empty()) {
        coverDecision.squares = coverCombos[0];
        // Choose a candidate that maximizes the highest value
        for (auto& combo : coverCombos) {
            int currentMax = 0;
            for (int n : combo)
                currentMax = max(currentMax, n);
            int bestMax = 0;
            for (int n : coverDecision.squares)
                bestMax = max(bestMax, n);
            if (currentMax > bestMax) {
                coverDecision.squares = combo;
            }
        }
    }
    else {
        coverDecision.squares.clear();
    }

    // Compute Uncover Decision
    uncoverDecision.squares.clear(); // Default to empty (no uncover move)

    // Only consider uncovering if explicitly allowed and our centralized conditions are met
    if (canUncover(diceSum, opponent, nullptr)) {
        vector<int> oppCovered;
        vector<int> oppSquares = opponent.getSquares();
        for (int i = 0; i < static_cast<int>(oppSquares.size()); i++) {
            if (oppSquares[i] != 0)  // Only consider covered squares.
                oppCovered.push_back(i + 1);
        }
        vector<vector<int>> uncoverCombos = Player::getCombinations(oppCovered, diceSum);

        if (!uncoverCombos.empty()) {
            uncoverDecision.squares = uncoverCombos[0];

            // Choose the candidate with the lower total.
            for (auto& combo : uncoverCombos) {
                int currentTotal = 0;
                for (int n : combo)
                    currentTotal += n;
                int bestTotal = 0;
                for (int n : uncoverDecision.squares)
                    bestTotal += n;
                if (currentTotal < bestTotal) {
                    uncoverDecision.squares = combo;
                }
            }
        }
    }

    // Heuristic Evaluation
    if (!coverDecision.squares.empty() && !uncoverDecision.squares.empty()) {
        int coverTotal = 0, uncoverTotal = 0, maxCover = 0;
        for (int n : coverDecision.squares) {
            coverTotal += n;
            maxCover = max(maxCover, n);
        }
        for (int n : uncoverDecision.squares) {
            uncoverTotal += n;
        }
        // Calculate scores:
        // For covering, a higher score is beneficial so adding extra weight to high-value squares.
        int coverScore = coverTotal + (2 * maxCover);
        // For uncovering, a lower total is preferable.
        int uncoverScore = uncoverTotal;

        string explanation;
        if (uncoverScore < coverScore) {
            // Uncover move is preferred.
            explanation = "Uncovering is recommended because the overall uncover score (" + to_string(uncoverScore)
                + ") is lower than the cover score (" + to_string(coverScore) + "). ";

            // Find the highest value square in the combination for context
            int highestSquare = 0;
            for (int sq : uncoverDecision.squares) {
                highestSquare = max(highestSquare, sq);
            }

            // Add specific explanation for individual squares
            if (uncoverDecision.squares.size() == 1) {
                // Single square case
                int sq = uncoverDecision.squares[0];
                if (sq >= 7) {
                    explanation += "Uncovering " + to_string(sq) + " is strategic as it's a high-value square that significantly reduces opponent's potential points.";
                }
                else if (sq >= 4) {
                    explanation += "Uncovering " + to_string(sq) + " targets a medium-value square, which is the best option available for this dice sum.";
                }
                else {
                    explanation += "Uncovering " + to_string(sq) + " is the only option available for this dice sum.";
                }
            }
            else {
                // Multiple squares case - explain the combination as a whole
                if (uncoverDecision.squares.size() > 1 && highestSquare >= 7) {
                    explanation += "This combination prioritizes uncovering " + to_string(highestSquare) +
                        " (a high-value square) while using smaller squares to complete the exact sum.";
                }
                else if (uncoverDecision.squares.size() > 1 && highestSquare >= 4) {
                    explanation += "This combination focuses on uncovering " + to_string(highestSquare) +
                        " (a medium-value square) while using smaller squares to reach the exact sum.";
                }
                else {
                    explanation += "This combination optimally uses the available squares to reach the required sum.";
                }
            }

            return MoveDecision{ false, uncoverDecision.squares, explanation };
        }
        else {
            // Cover move is preferred.
            explanation = "I recommend covering because the cover score (" + to_string(coverScore)
                + ") is higher than the uncover score (" + to_string(uncoverScore) + "). ";

            // Find the highest value square in the combination for context
            int highestSquare = 0;
            for (int sq : coverDecision.squares) {
                highestSquare = max(highestSquare, sq);
            }

            // Add specific explanation for individual squares
            if (coverDecision.squares.size() == 1) {
                // Single square case
                int sq = coverDecision.squares[0];
                if (sq >= 7) {
                    explanation += "Covering " + to_string(sq) + " is crucial as it's a high-value square that protects against major point loss.";
                }
                else if (sq >= 4) {
                    explanation += "Covering " + to_string(sq) + " secures a medium-value square, which is the best option available for this dice sum.";
                }
                else {
                    explanation += "Covering " + to_string(sq) + " is the only option available for this dice sum.";
                }
            }
            else {
                // Multiple squares case - explain the combination as a whole
                if (coverDecision.squares.size() > 1 && highestSquare >= 7) {
                    explanation += "This combination prioritizes covering " + to_string(highestSquare) +
                        " (a high-value square) while using smaller squares to complete the exact sum.";
                }
                else if (coverDecision.squares.size() > 1 && highestSquare >= 4) {
                    explanation += "This combination focuses on covering " + to_string(highestSquare) +
                        " (a medium-value square) while using smaller squares to reach the exact sum.";
                }
                else {
                    explanation += "This combination optimally uses the available squares to reach the required sum.";
                }
            }

            return MoveDecision{ true, coverDecision.squares, explanation };
        }
    }
    // If only an uncover move is available.
    else if (!uncoverDecision.squares.empty()) {
        string explanation = "Only an uncover move is available. ";

        // Find the highest value square in the combination
        int highestSquare = 0;
        for (int sq : uncoverDecision.squares) {
            highestSquare = max(highestSquare, sq);
        }

        // Explain based on combination size and highest value
        if (uncoverDecision.squares.size() == 1) {
            // Single square case
            int sq = uncoverDecision.squares[0];
            if (sq >= 7) {
                explanation += "Uncovering " + to_string(sq) + " is highly advantageous as it targets a high-value square.";
            }
            else if (sq >= 4) {
                explanation += "Uncovering " + to_string(sq) + " targets a medium-value square, which is the best option available.";
            }
            else {
                explanation += "Uncovering " + to_string(sq) + " is the only option available for this dice sum.";
            }
        }
        else {
            // Multiple squares case
            if (uncoverDecision.squares.size() > 1 && highestSquare >= 7) {
                explanation += "This combination prioritizes uncovering " + to_string(highestSquare) +
                    " (a high-value square) while using smaller squares to complete the exact sum.";
            }
            else if (uncoverDecision.squares.size() > 1 && highestSquare >= 4) {
                explanation += "This combination focuses on uncovering " + to_string(highestSquare) +
                    " (a medium-value square) while using smaller squares to reach the exact sum.";
            }
            else {
                explanation += "This combination optimally uses the available squares to reach the required sum.";
            }
        }

        return MoveDecision{ false, uncoverDecision.squares, explanation };
    }
    // Otherwise, only a cover move is available or there's no valid uncover move due to restrictions
    else {
        string explanation = "Only a cover move is available. ";

        // Explain why uncovering isn't an option (if there are covered squares to potentially uncover)
        bool opponentHasCoveredSquares = false;
        vector<int> oppSquares = opponent.getSquares();
        for (int sq : oppSquares) {
            if (sq != 0) {
                opponentHasCoveredSquares = true;
                break;
            }
        }

        //if (opponentHasCoveredSquares && !allowUncover) {
        //    explanation += "Uncovering is not allowed on the first turn. ";
        //}
        if (opponentHasCoveredSquares && !canUncover(diceSum, opponent, nullptr)) {
            // Check if it's a handicap protection issue
            if (opponent.getName() == "Computer" || opponent.getName() == "Human") {
                explanation += "Uncovering may be restricted due to handicap protection or lack of valid combinations. ";
            }
        }

        // If no cover move is available either, return empty decision
        if (coverDecision.squares.empty()) {
            return MoveDecision{ true, vector<int>(), "No valid moves available for this dice sum." };
        }

        // Otherwise continue with the cover move explanation
        int highestSquare = 0;
        for (int sq : coverDecision.squares) {
            highestSquare = max(highestSquare, sq);
        }

        // Explain based on combination size and highest value
        if (coverDecision.squares.size() == 1) {
            // Single square case
            int sq = coverDecision.squares[0];
            if (sq >= 7) {
                explanation += "Covering " + to_string(sq) + " is a priority as it's a high-value square that needs protection.";
            }
            else if (sq >= 4) {
                explanation += "Covering " + to_string(sq) + " secures a medium-value square, which is the best option available.";
            }
            else {
                explanation += "Covering " + to_string(sq) + " is the only option available for this dice sum.";
            }
        }
        else {
            // Multiple squares case
            if (coverDecision.squares.size() > 1 && highestSquare >= 7) {
                explanation += "This combination prioritizes covering " + to_string(highestSquare) +
                    " (a high-value square) while using smaller squares to complete the exact sum.";
            }
            else if (coverDecision.squares.size() > 1 && highestSquare >= 4) {
                explanation += "This combination focuses on covering " + to_string(highestSquare) +
                    " (a medium-value square) while using smaller squares to reach the exact sum.";
            }
            else {
                explanation += "This combination optimally uses the available squares to reach the required sum.";
            }
        }

        return MoveDecision{ true, coverDecision.squares, explanation };
    }
}
    /* *********************************************************************
Function Name: offerHint
Purpose: To provide a hint for the player's move. (Placeholder function.)
Parameters: None.
Return Value: None.
Algorithm:
         1) Print a message indicating that hint functionality is not yet implemented.
Reference: AI recommended
********************************************************************* */
void Player::offerHint() {
    cout << "[" << playerName << "] HINT: (Not yet implemented)\n";
}