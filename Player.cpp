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

/* *********************************************************************
Function Name: getOptimalDiceRollWithReason
Purpose: Determines the strategic choice between rolling one or two dice
         based on a comprehensive analysis of the game state. This method should
         only be called when squares 7 through n are all covered, giving the player
         a choice of dice count. Otherwise game rules mandate using two dice.
Parameters: None.
Return Value: A pair containing:
              - an integer (1 or 2) representing the optimal number of dice to roll
              - a string explaining the reasoning behind the decision
Algorithm:
         1) Analyze the full board to count uncovered squares and their values
         2) Calculate probability distributions for one die vs two dice
         3) Evaluate strategic factors (progress toward covering all squares)
         4) Make a decision based on maximizing expected value
         5) Generate a detailed explanation of the reasoning
Reference: None
********************************************************************* */
std::pair<int, std::string> Player::getOptimalDiceRollWithReason() const {
    // Count uncovered squares
    int totalUncovered = 0;
    int lowValueUncovered = 0;  // Squares 1-4
    int midValueUncovered = 0;  // Squares 5-9
    int highValueUncovered = 0; // Squares 10-11 (if present)
    std::vector<int> uncoveredValues;

    for (int i = 0; i < squares.size(); i++) {
        if (squares[i] == 0) { // Uncovered square
            totalUncovered++;
            int squareValue = i + 1;
            uncoveredValues.push_back(squareValue);

            if (squareValue <= 4) lowValueUncovered++;
            else if (squareValue <= 9) midValueUncovered++;
            else highValueUncovered++;
        }
    }

    // Calculate progress (percentage of squares covered)
    double progressPercentage = 100.0 * (squares.size() - totalUncovered) / squares.size();

    // If no squares are uncovered, default to one die with explanation
    if (totalUncovered == 0) {
        return { 1, "All squares are already covered. One die provides more control for potential uncover moves." };
    }

    // If very few squares remain, specific tactical decisions apply
    if (totalUncovered <= 2) {
        std::string remainingDesc = "";
        for (int val : uncoveredValues) {
            remainingDesc += std::to_string(val) + " ";
        }

        return { 1, "Only " + std::to_string(totalUncovered) + " square(s) remain uncovered (" +
                remainingDesc + "). Rolling one die gives better precision for these specific values." };
    }

    // Calculate expected values for different strategies

    // For one die: values 1-6
    int oneCount = 0;
    for (int i = 1; i <= 6; i++) {
        // Count how many combinations we can make with this value
        if (canCoverSum(uncoveredValues, i)) {
            oneCount++;
        }
    }
    double oneDieProb = oneCount / 6.0;

    // For two dice: values 2-12
    int twoCount = 0;
    // Probability distribution for two dice
    const std::vector<double> twoDiceProbs = {
        0,     // 0 (not possible)
        0,     // 1 (not possible)
        1 / 36.0, // 2
        2 / 36.0, // 3
        3 / 36.0, // 4
        4 / 36.0, // 5
        5 / 36.0, // 6
        6 / 36.0, // 7
        5 / 36.0, // 8
        4 / 36.0, // 9
        3 / 36.0, // 10
        2 / 36.0, // 11
        1 / 36.0  // 12
    };

    for (int i = 2; i <= 12; i++) {
        if (canCoverSum(uncoveredValues, i)) {
            twoCount += twoDiceProbs[i] * 36; // Scale back to count out of 36
        }
    }
    double twoDiceProb = twoCount / 36.0;

    // Decision factors
    std::string explanation;
    int decision;

    // Special case: very high progress
    if (progressPercentage >= 75) {
        if (highValueUncovered > 0) {
            decision = 2;
            explanation = "Board is " + std::to_string(static_cast<int>(progressPercentage)) +
                "% covered, but high-value squares (" +
                std::to_string(highValueUncovered) +
                ") remain uncovered. Rolling two dice increases chances of getting higher sums.";
        }
        else {
            decision = 1;
            explanation = "Board is " + std::to_string(static_cast<int>(progressPercentage)) +
                "% covered with only low/mid-value squares remaining. Rolling one die gives more precise control.";
        }
    }
    // Decision based on uncovered square distribution
    else if (highValueUncovered > lowValueUncovered && midValueUncovered > lowValueUncovered) {
        decision = 2;
        explanation = "More mid/high-value squares (" +
            std::to_string(midValueUncovered + highValueUncovered) +
            ") remain uncovered than low-value squares (" +
            std::to_string(lowValueUncovered) +
            "). Rolling two dice gives better chances for higher sums needed.";
    }
    else if (lowValueUncovered >= totalUncovered / 2) {
        decision = 1;
        explanation = "Majority of uncovered squares (" +
            std::to_string(lowValueUncovered) + " out of " +
            std::to_string(totalUncovered) +
            ") are low-value (1-4). One die provides better precision for these values.";
    }
    // Decision based on probability comparison
    else if (oneDieProb > twoDiceProb) {
        decision = 1;
        explanation = "Probability analysis shows one die gives " +
            std::to_string(static_cast<int>(oneDieProb * 100)) +
            "% chance of useful rolls vs " +
            std::to_string(static_cast<int>(twoDiceProb * 100)) +
            "% for two dice. One die is statistically advantageous.";
    }
    else {
        decision = 2;
        explanation = "Probability analysis shows two dice give " +
            std::to_string(static_cast<int>(twoDiceProb * 100)) +
            "% chance of useful rolls vs " +
            std::to_string(static_cast<int>(oneDieProb * 100)) +
            "% for one die. Two dice are statistically advantageous.";
    }

    return { decision, explanation };
}

/* *********************************************************************
Function Name: canCoverSum
Purpose: Helper method to check if there exists any combination of the given
         values that sums to the target value.
Parameters:
         values - a vector of integers representing available values
         target - an integer representing the sum to reach
Return Value: Boolean indicating whether a valid combination exists.
Algorithm:
         1) Use a recursive approach to check subsets
         2) Terminate when a valid subset is found or all options exhausted
Reference: None
********************************************************************* */
bool Player::canCoverSum(const std::vector<int>& values, int target) const {
    // Dynamic programming approach to subset sum problem
    // Limited to 4 elements max as per game rules

    // For very simple cases
    if (target == 0) return true;
    if (values.empty() || target < 0) return false;

    // Check if any single value equals target
    for (int val : values) {
        if (val == target) return true;
    }

    // Check pairs (2 values)
    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = i + 1; j < values.size(); j++) {
            if (values[i] + values[j] == target) return true;
        }
    }

    // Check triplets (3 values)
    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = i + 1; j < values.size(); j++) {
            for (size_t k = j + 1; k < values.size(); k++) {
                if (values[i] + values[j] + values[k] == target) return true;
            }
        }
    }

    // Check quadruplets (4 values)
    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = i + 1; j < values.size(); j++) {
            for (size_t k = j + 1; k < values.size(); k++) {
                for (size_t l = k + 1; l < values.size(); l++) {
                    if (values[i] + values[j] + values[k] + values[l] == target) return true;
                }
            }
        }
    }

    return false;
}

/* *********************************************************************
Function Name: optimalDiceRoll
Purpose: Simplified interface to get optimal dice roll decision without explanation.
Parameters: None.
Return Value: An integer (1 or 2) representing the optimal number of dice to roll.
Algorithm:
         1) Call getOptimalDiceRollWithReason() and return only the decision component.
Reference: None
********************************************************************* */
int Player::optimalDiceRoll() const {
    return getOptimalDiceRollWithReason().first;
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
Function Name: formatNumberList
Purpose: Helper function to format a list of numbers with proper commas and "and"
Parameters:
         numbers - a vector of integers to format
Return Value: A string containing the formatted list
Algorithm:
         1) For empty lists, return an empty string
         2) For a single item, return that item as a string
         3) For multiple items, add commas between all but the last two items
         4) Add " and " between the last two items
Reference: None
********************************************************************* */
std::string Player::formatNumberList(const std::vector<int>& numbers) const {
    if (numbers.empty()) return "";

    if (numbers.size() == 1) {
        return std::to_string(numbers[0]);
    }

    std::string result;
    for (size_t i = 0; i < numbers.size(); i++) {
        result += std::to_string(numbers[i]);
        if (i < numbers.size() - 2) {
            result += ", ";
        }
        else if (i == numbers.size() - 2) {
            result += " and ";
        }
    }

    return result;
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



MoveDecision Player::decideMove(int diceSum, const Player& opponent, bool allowUncover, const Tournament* tournamentPtr) {
    MoveDecision coverDecision, uncoverDecision;
    coverDecision.cover = true;   // default for covering
    uncoverDecision.cover = false; // default for uncovering


    // *** MOVED TO BEGINNING: Check if handicap blocking is in effect ***
// Check opponent squares and handicap protection
    bool opponentHasCoveredSquares = false;
    vector<int> oppSquares = opponent.getSquares();
    for (int sq : oppSquares) {
        if (sq != 0) {
            opponentHasCoveredSquares = true;
            break;
        }
    }

    bool handicapBlocking = tournamentPtr && tournamentPtr->getHandicapActive() &&
        opponent.getName() == tournamentPtr->getAdvantagePlayerName() &&
        !opponent.getHasHadTurnInRound();

    // Force covering in these cases (handicap block logic mirror from Human.cpp)
    bool forceCovering = false;
    if (!opponentHasCoveredSquares || handicapBlocking || !canUncover(diceSum, opponent, tournamentPtr)) {
        forceCovering = true;
    }

    // Step 1: Generate all valid cover combinations
    vector<int> myAvailable;
    for (int i = 0; i < static_cast<int>(squares.size()); i++) {
        if (squares[i] == 0)
            myAvailable.push_back(i + 1);
    }
    vector<vector<int>> coverCombos = Player::getCombinations(myAvailable, diceSum);


    // Step 2: Find the optimal cover move if any valid moves exist
    if (!coverCombos.empty()) {
        // Enhanced strategy: Evaluate each cover combination
        int bestCoverScore = -1;
        string bestCoverExplanation;

        for (const auto& combo : coverCombos) {
            // Safety check - skip empty combos
            if (combo.empty()) continue;

            // Calculate basic score: sum of squares plus bonus for high values
            int comboSum = 0;
            int maxSquare = 0;
            int squareCount = combo.size();

            for (int square : combo) {
                comboSum += square;
                maxSquare = std::max(maxSquare, square);
            }

            // Base score calculation
            int score = comboSum + (2 * maxSquare);

            // Endgame detection - check if this move would win the game
            bool wouldWin = true;
            vector<int> simulatedBoard = squares;
            for (int sq : combo) {
                if (sq - 1 >= 0 && sq - 1 < static_cast<int>(simulatedBoard.size())) {
                    simulatedBoard[sq - 1] = sq; // Mark as covered
                }
            }

            // Check if all squares would be covered after this move
            for (int val : simulatedBoard) {
                if (val == 0) {
                    wouldWin = false;
                    break;
                }
            }

            // Massive bonus for winning moves
            if (wouldWin) {
                score += 1000;
            }

            // Bonus for covering high-value squares
            if (maxSquare >= 7) {
                score += 15;
            }
            else if (maxSquare >= 5) {
                score += 8;
            }

            // Bonus for covering multiple squares efficiently
            if (squareCount > 1) {
                score += squareCount * 3;
            }

            // Bonus for covering consecutive squares (tactical advantage)
            bool hasConsecutive = false;
            // Create a copy of combo that we can sort
            vector<int> sortedCombo = combo;
            std::sort(sortedCombo.begin(), sortedCombo.end());
            for (size_t i = 1; i < sortedCombo.size(); i++) {
                if (sortedCombo[i] == sortedCombo[i - 1] + 1) {
                    hasConsecutive = true;
                    break;
                }
            }
            if (hasConsecutive) {
                score += 5;
            }

            // Update best cover decision if this is better
            if (score > bestCoverScore) {
                bestCoverScore = score;
                coverDecision.squares = combo;

                // Generate explanation
                if (combo.size() == 1) {
                    bestCoverExplanation = "Cover square: " + formatNumberList(combo);
                }
                else {
                    bestCoverExplanation = "Cover squares: " + formatNumberList(combo);
                }

                if (wouldWin) {
                    bestCoverExplanation += " because it would win the game by covering all squares!";
                }
                else if (combo.size() > 1) {
                    // Sort squares by value to identify high and low values
                    vector<int> sortedSquares = combo;
                    std::sort(sortedSquares.begin(), sortedSquares.end());

                    // Safety check before accessing front/back
                    if (!sortedSquares.empty()) {
                        int lowestSquare = sortedSquares.front();
                        int highestSquare = sortedSquares.back();

                        // Different explanations based on the combination of values
                        if (highestSquare >= 7 && lowestSquare <= 4) {
                            // Count how many low-value squares we have
                            vector<int> lowValueSquares;
                            for (int sq : sortedSquares) {
                                if (sq <= 4) {
                                    lowValueSquares.push_back(sq);
                                }
                            }

                            // Create explanation based on the number of low-value squares
                            bestCoverExplanation += " because it is a strategic combination that covers high-value square " +
                                std::to_string(highestSquare) +
                                " while efficiently using low-value square";

                            // Add 's' if multiple low-value squares
                            if (lowValueSquares.size() > 1) {
                                bestCoverExplanation += "s ";
                            }
                            else {
                                bestCoverExplanation += " ";
                            }

                            // Add all low-value squares
                            for (size_t i = 0; i < lowValueSquares.size(); i++) {
                                bestCoverExplanation += std::to_string(lowValueSquares[i]);

                                if (i < lowValueSquares.size() - 2) {
                                    bestCoverExplanation += ", ";
                                }
                                else if (i == lowValueSquares.size() - 2) {
                                    bestCoverExplanation += " and ";
                                }
                            }

                            bestCoverExplanation += " to reach the exact sum.";
                        }

                        else if (highestSquare >= 7) {
                            bestCoverExplanation += " because it is strategic as it covers high-value square " +
                                std::to_string(highestSquare) + ".";
                        }
                        else if (highestSquare >= 5) {
                            // For mid-value square combinations
                            if (squareCount == 2) {
                                bestCoverExplanation += " because it balances efficiency with strategic value by covering mid-value square " +
                                    std::to_string(highestSquare) + " along with square " +
                                    std::to_string(sortedSquares.front()) + ".";
                            }
                            else if (squareCount > 2) {
                                bestCoverExplanation += " because it strategically covers mid-value square " +
                                    std::to_string(highestSquare) + " while efficiently using " +
                                    std::to_string(squareCount - 1) + " additional squares to match the dice sum.";
                            }
                        }
                        else if (squareCount > 2) {
                            bestCoverExplanation += " because it efficiently combines " + std::to_string(squareCount) +
                                " squares to maximize coverage with the given dice sum.";
                        }
                        else if (squareCount == 2) {
                            int firstSquare = sortedSquares.front();
                            int secondSquare = sortedSquares.back();
                            bestCoverExplanation += " because it uses the exact combination needed (" +
                                std::to_string(firstSquare) + " + " + std::to_string(secondSquare) +
                                " = " + std::to_string(firstSquare + secondSquare) +
                                ") to match the dice sum.";
                        }
                        else {
                            bestCoverExplanation += " because it is the best available option for the given dice sum.";
                        }
                    }
                }
                else if (combo.size() == 1) {
                    // Single square case - safe to access first element
                    int square = combo[0];
                    if (square >= 7) {
                        bestCoverExplanation += " because it is strategic as it covers high-value square " +
                            std::to_string(square) + ".";
                    }
                    else if (square >= 5) {
                        bestCoverExplanation += " because it covers mid-value square " + std::to_string(square) + ", which provides good strategic value.";
                    }
                    else {
                        bestCoverExplanation += " because it covers a low-value square " + std::to_string(square) + ", which is the best option for this dice roll.";
                    }
                }
                else {
                    // Should never reach here (empty combo) but added for safety
                    bestCoverExplanation += " because it is the best available option.";
                }
            }
        }

        // Store the explanation for the best cover move
        coverDecision.explanation = bestCoverExplanation;
    }
    else {
        coverDecision.squares.clear();
    }

    // Step 3: Generate all valid uncover combinations (only if allowed by game rules)
    uncoverDecision.squares.clear(); // Default to empty (no uncover move)

    // Only consider uncovering if explicitly allowed by game rules and our centralized conditions are met
    if (opponentHasCoveredSquares && !handicapBlocking && canUncover(diceSum, opponent, tournamentPtr)) {
        vector<int> oppCovered;
        vector<int> oppSquares = opponent.getSquares();

        // Check if handicap is active for filtering out the handicap square
        bool isHandicapActive = tournamentPtr && tournamentPtr->getHandicapActive() &&
            opponent.getName() == tournamentPtr->getAdvantagePlayerName() &&
            !opponent.getHasHadTurnInRound();
        int handicapSquare = isHandicapActive ? tournamentPtr->getHandicapSquare() : 0;

        // Only add squares that aren't protected by handicap
        for (int i = 0; i < static_cast<int>(oppSquares.size()); i++) {
            if (oppSquares[i] != 0) {  // Only consider covered squares
                int squareLabel = i + 1;
                // Skip the handicap square if it's protected
                if (isHandicapActive && squareLabel == handicapSquare) {
                    continue;  // Skip adding this square to available options
                }
                oppCovered.push_back(squareLabel);
            }
        }

        vector<vector<int>> uncoverCombos = Player::getCombinations(oppCovered, diceSum);

        if (!uncoverCombos.empty()) {
            // Enhanced strategy: Evaluate each uncover combination
            int bestUncoverScore = -1;
            string bestUncoverExplanation;

            for (const auto& combo : uncoverCombos) {
                // Safety check - skip empty combos
                if (combo.empty()) continue;

                // Calculate basic score
                int comboSum = 0;
                int maxSquare = 0;
                int squareCount = combo.size();

                for (int square : combo) {
                    comboSum += square;
                    maxSquare = std::max(maxSquare, square);
                }

                // For uncovering, we generally want the lowest sum (most efficient)
                // But with strategic considerations
                int score = 100 - comboSum;  // Base score: Lower sum is better

                // Check if this move would win the game by uncovering all opponent squares
                bool wouldWin = true;
                vector<int> simulatedOpponentBoard = oppSquares;
                for (int sq : combo) {
                    if (sq - 1 >= 0 && sq - 1 < static_cast<int>(simulatedOpponentBoard.size())) {
                        simulatedOpponentBoard[sq - 1] = 0; // Mark as uncovered
                    }
                }

                // Check if all opponent squares would be uncovered after this move
                for (int val : simulatedOpponentBoard) {
                    if (val != 0) {
                        wouldWin = false;
                        break;
                    }
                }

                // Massive bonus for winning moves
                if (wouldWin) {
                    score += 1000;
                }

                // Bonus for uncovering high-value squares
                if (maxSquare >= 7) {
                    score += 10;  // Significant bonus for high-value squares
                }

                // Bonus for strategically uncovering multiple squares
                if (squareCount > 1) {
                    score += squareCount * 2;
                }

                // Update best uncover decision if this is better
                if (score > bestUncoverScore) {
                    bestUncoverScore = score;
                    uncoverDecision.squares = combo;

                    // Generate explanation
                    if (combo.size() == 1) {
                        bestUncoverExplanation = "Uncover square: " + formatNumberList(combo);
                    }
                    else {
                        bestUncoverExplanation = "Uncover squares: " + formatNumberList(combo);
                    }

                    if (wouldWin) {
                        bestUncoverExplanation += " because it would win the game by uncovering all opponent's squares!";
                    }
                    else if (combo.size() > 1) {
                        // Sort squares by value to identify high and low values
                        vector<int> sortedSquares = combo;
                        std::sort(sortedSquares.begin(), sortedSquares.end());

                        // Safety check before accessing front/back
                        if (!sortedSquares.empty()) {
                            int lowestSquare = sortedSquares.front();
                            int highestSquare = sortedSquares.back();

                            // Different explanations based on the combination of values
                            if (highestSquare >= 7 && lowestSquare <= 4) {
                                // Count how many low-value squares we have
                                vector<int> lowValueSquares;
                                for (int sq : sortedSquares) {
                                    if (sq <= 4) {
                                        lowValueSquares.push_back(sq);
                                    }
                                }

                                // Create explanation based on the number of low-value squares
                                bestUncoverExplanation += " because it targets the high-value square " +
                                    std::to_string(highestSquare) +
                                    " while using low-value square";

                                // Add 's' if multiple low-value squares
                                if (lowValueSquares.size() > 1) {
                                    bestUncoverExplanation += "s ";
                                }
                                else {
                                    bestUncoverExplanation += " ";
                                }

                                // Add all low-value squares
                                for (size_t i = 0; i < lowValueSquares.size(); i++) {
                                    bestUncoverExplanation += std::to_string(lowValueSquares[i]);

                                    if (i < lowValueSquares.size() - 2) {
                                        bestUncoverExplanation += ", ";
                                    }
                                    else if (i == lowValueSquares.size() - 2) {
                                        bestUncoverExplanation += " and ";
                                    }
                                }

                                bestUncoverExplanation += " to complete the combination.";
                            }
                            else if (highestSquare >= 7) {
                                bestUncoverExplanation += " targets the high-value square " +
                                    std::to_string(highestSquare) + ".";
                            }
                            else if (highestSquare >= 5) {
                                // For mid-value square combinations
                                if (squareCount == 2) {
                                    bestUncoverExplanation += " because it focuses on mid-value square " +
                                        std::to_string(highestSquare) + " along with square " +
                                        std::to_string(sortedSquares.front()) + " to match the dice sum precisely.";
                                }
                                else if (squareCount > 2) {
                                    bestUncoverExplanation += " because it strategically targets mid-value square " +
                                        std::to_string(highestSquare) + " while using " +
                                        std::to_string(squareCount - 1) + " additional squares to match the exact sum.";
                                }
                            }
                            else if (squareCount > 2) {
                                bestUncoverExplanation += " because it efficiently targets " + std::to_string(squareCount) +
                                    " squares to maximize uncovering with the given dice sum.";
                            }
                            else if (squareCount == 2) {
                                int firstSquare = sortedSquares.front();
                                int secondSquare = sortedSquares.back();
                                bestUncoverExplanation += " because it specifically targets the combination of squares " +
                                    std::to_string(firstSquare) + " and " + std::to_string(secondSquare) +
                                    " which sum to " + std::to_string(firstSquare + secondSquare) +
                                    ", matching the dice roll perfectly.";
                            }
                            else {
                                bestUncoverExplanation += " because it is optimal for the given dice sum.";
                            }
                        }
                    }
                    else if (combo.size() == 1) {
                        // Single square case - safe to access first element
                        int square = combo[0];
                        if (square >= 7) {
                            bestUncoverExplanation += " because it targets the high-value square " +
                                std::to_string(square) + ".";
                        }
                        else if (square >= 5) {
                            bestUncoverExplanation += " because it targets mid-value square " + std::to_string(square) + ", providing good tactical advantage.";
                        }
                        else {
                            bestUncoverExplanation += " because it targets a low-value square " + std::to_string(square) + ", which is necessary given the current dice roll.";
                        }
                    }
                    else {
                        // Should never reach here (empty combo) but added for safety
                        bestUncoverExplanation += " because it is the best available option.";
                    }

                    // Store the explanation for the best uncover move
                    uncoverDecision.explanation = bestUncoverExplanation;
                }
            }
        }
    }

    // Step 4: Make the final decision between covering and uncovering
    if (!coverDecision.squares.empty() && !uncoverDecision.squares.empty() && !forceCovering) {
        // Both moves are available - calculate strategic scores for comparison
        int coverTotal = 0, uncoverTotal = 0, maxCover = 0, maxUncover = 0;
        bool coverWouldWin = false, uncoverWouldWin = false;

        // Calculate cover scores
        for (int n : coverDecision.squares) {
            coverTotal += n;
            maxCover = std::max(maxCover, n);
        }

        // Calculate uncover scores
        for (int n : uncoverDecision.squares) {
            uncoverTotal += n;
            maxUncover = std::max(maxUncover, n);
        }

        // Check for winning moves
        vector<int> tempSquares = squares;
        for (int sq : coverDecision.squares) {
            if (sq - 1 >= 0 && sq - 1 < static_cast<int>(tempSquares.size())) {
                tempSquares[sq - 1] = sq;
            }
        }
        coverWouldWin = true;
        for (int val : tempSquares) {
            if (val == 0) {
                coverWouldWin = false;
                break;
            }
        }

        vector<int> tempOppSquares = opponent.getSquares();
        for (int sq : uncoverDecision.squares) {
            if (sq - 1 >= 0 && sq - 1 < static_cast<int>(tempOppSquares.size())) {
                tempOppSquares[sq - 1] = 0;
            }
        }
        uncoverWouldWin = true;
        for (int val : tempOppSquares) {
            if (val != 0) {
                uncoverWouldWin = false;
                break;
            }
        }

        // If either move is a winning move, prioritize that
        if (coverWouldWin && !uncoverWouldWin) {
            string explanation = "Covering is recommended because it will win the game by covering all my squares. " +
                coverDecision.explanation;
            return MoveDecision{ true, coverDecision.squares, explanation };
        }
        else if (!coverWouldWin && uncoverWouldWin) {
            string explanation = "Uncovering is recommended because it will win the game by uncovering all opponent's squares. " +
                uncoverDecision.explanation;
            return MoveDecision{ false, uncoverDecision.squares, explanation };
        }
        else if (coverWouldWin && uncoverWouldWin) {
            // Both would win - make a strategic choice based on score potential
            int coverScore = 0, uncoverScore = 0;

            // Calculate potential score for cover win (sum of opponent's uncovered squares)
            for (size_t i = 0; i < tempOppSquares.size(); i++) {
                if (tempOppSquares[i] == 0) {
                    coverScore += static_cast<int>(i) + 1;
                }
            }

            // Calculate potential score for uncover win (sum of own covered squares)
            for (size_t i = 0; i < tempSquares.size(); i++) {
                if (tempSquares[i] != 0) {
                    uncoverScore += tempSquares[i];
                }
            }

            if (uncoverScore > coverScore) {
                string explanation = "Both moves would win the game, but uncovering yields a higher score (" +
                    std::to_string(uncoverScore) + " vs " + std::to_string(coverScore) +
                    "). " + uncoverDecision.explanation;
                return MoveDecision{ false, uncoverDecision.squares, explanation };
            }
            else {
                string explanation = "Both moves would win the game, but covering yields a higher score (" +
                    std::to_string(coverScore) + " vs " + std::to_string(uncoverScore) +
                    "). " + coverDecision.explanation;
                return MoveDecision{ true, coverDecision.squares, explanation };
            }
        }

        // Neither move wins immediately - use enhanced strategic scoring
        int coverScore = coverTotal + (3 * maxCover);
        if (maxCover >= 7) coverScore += 10;  // Bonus for high-value squares

        int uncoverScore = 100 - uncoverTotal + (2 * maxUncover);
        if (maxUncover >= 7) uncoverScore += 15;  // Higher bonus for targeting opponent's high squares

        // Add bonus for multi-square moves
        coverScore += static_cast<int>(coverDecision.squares.size()) * 3;
        uncoverScore += static_cast<int>(uncoverDecision.squares.size()) * 2;

        // Make final decision with explanation
        if (uncoverScore > coverScore) {
            string explanation = "Uncovering is recommended with strategic score " + std::to_string(uncoverScore) +
                " versus cover score " + std::to_string(coverScore) + ". " +
                uncoverDecision.explanation;
            return MoveDecision{ false, uncoverDecision.squares, explanation };
        }
        else {
            string explanation = "Covering is recommended with strategic score " + std::to_string(coverScore) +
                " versus uncover score " + std::to_string(uncoverScore) + ". " +
                coverDecision.explanation;
            return MoveDecision{ true, coverDecision.squares, explanation };
        }
    }

    // Step 5: Handle cases where only one type of move is available
    else if (!uncoverDecision.squares.empty() && !forceCovering) {
        string explanation = "Only an uncover move is available. \n" + uncoverDecision.explanation;
        return MoveDecision{ false, uncoverDecision.squares, explanation };
    }
    // Otherwise, only a cover move is available or there's no valid uncover move
    else {
        // If no cover move is available either, return empty decision
        if (coverDecision.squares.empty()) {
            return MoveDecision{ true, vector<int>(), "No valid moves available for this dice sum. \n" };
        }


        string explanation = coverDecision.explanation;


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