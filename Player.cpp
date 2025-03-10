/************************************************************
 * Name:     Lucas Maretzo
 * Project:  P1 Canoga
 * Class:    CMPS366 Operating Systems
 * Date:     3/10/2025
 ************************************************************/

#include "Player.h"
#include <iostream> 
#include <algorithm>
#include "Tournament.h"
#include <algorithm> 

using namespace std;


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
Reference: AI
********************************************************************* */
void Player::findCombinations(const vector<int>& nums, int target, int start,
    vector<int>& current, vector<vector<int>>& result) {
    if (target == 0 && current.size() >= 1 && current.size() <= 4) {
        result.push_back(current);
    }
    // Cannot choose more than 4 squares
    if (current.size() == 4) return;
    for (int i = start; i < nums.size(); i++) {
        if (nums[i] > target)
            // skip numbers that are too large
            continue;
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
    // Ensure board is marked unmodified.
    boardModified = false;
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

    // Ensure board is marked unmodified.
    boardModified = false;
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
    // Reset squares dynamically based on the board size
    squares.assign(boardSize, 0);

    // Mark the board as unmodified.
    boardModified = false; 
}

Player::~Player()
{
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
Function Name: isBoardModified
Purpose: To check if the board has been modified from its initial state.
Parameters: None.
Return Value: A boolean value; true if at least one square is covered, false otherwise.
Algorithm:
         1) Return the value of boardModified.
Reference: None
********************************************************************* */
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
        // Already covered.
        return false;
    }

    // Now it is covered.
    squares[idx] = squareLabel;

    // Mark the board as modified.
    boardModified = true; 
    return true;
}

/* *********************************************************************
Function Name: uncoverSquare
Purpose: To mark a square on the player's board as uncovered.
Parameters:
         squareLabel - an integer (1-based index) representing the square to uncover
         tournamentPtr - a pointer to the Tournament object for handicap rules (optional)
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
        // Already is uncovered.
        return false;
    }

    // Now it is uncovered.
    squares[idx] = 0;

    // Mark the board as modified.
    boardModified = true;

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
bool Player::canUncover(int diceSum, const Player& opponent, const Tournament* tPtr) const
{
    // 1) Does the opponent have any covered squares
    bool hasCovered = false;
    vector<int> oppSquares = opponent.getSquares();
    for (int val : oppSquares) {
        // Non-zero means covered
        if (val != 0) {  
            hasCovered = true;
            break;
        }
    }
    if (!hasCovered) {
        return false;
    }

    // 2) Check if handicap blocks uncover
    if (tPtr && tPtr->getHandicapActive() &&
        opponent.getName() == tPtr->getAdvantagePlayerName() &&
        !opponent.getHasHadTurnInRound()) {
        return false;
    }

    // 3) Find valid combos to uncover
    vector<int> coveredLabels;
    for (int i = 0; i < static_cast<int>(oppSquares.size()); i++) {
        // Means covered
        if (oppSquares[i] != 0) {
            coveredLabels.push_back(i + 1);
        }
    }

    auto combos = getCombinations(coveredLabels, diceSum);
    return !combos.empty();
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
    // This returns a copy
    return squares;
}

/* *********************************************************************
Function Name: setSquares
Purpose: To update the player's board state with a new configuration.
Parameters:
         newSquares - a constant reference to a vector of integers representing the new board state
Return Value: None.
Algorithm:
         1) Assign newSquares to the squares vector.
         2) Check if any squares are covered and update boardModified flag accordingly.
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
Purpose: To set the player's score to a specified value.
Parameters:
         newScore - an integer representing the new score value
Return Value: None.
Algorithm: Assign the provided value to the score variable.
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
    // End the top border
    cout << "+" << endl;

    // Generate the row content dynamically
    for (int i = 0; i < squares.size(); ++i) {
        if (squares[i] == 0) {

            // Uncovered square shows its number
            if (i + 1 < 10) {

                // Single-digit alignment
                cout << "| " << (i + 1) << " ";
            }
            else {

                // Double-digit alignment
                cout << "| " << (i + 1);
            }
        }
        else {

            // Covered square shows "X"
            cout << "| X ";
        }
    }

    // End the row content
    cout << "|" << endl;

    // Generate the bottom border dynamically
    for (int i = 0; i < squares.size(); ++i) {
        cout << "+---";
    }

    // End the bottom border
    cout << "+" << endl;

    cout << endl;
}

/* *********************************************************************
Function Name: getOptimalDiceRollWithReason
Purpose: Determines the strategic choice between rolling one or two dice
         when squares 7-n are already covered, with enhanced statistical analysis
         that accounts for covering multiple squares with one roll.
Parameters: None.
Return Value: A pair containing:
              - an integer (1 or 2) representing the optimal number of dice to roll
              - a string explaining the reasoning behind the decision
Algorithm:
         1) Analyze squares 1-6 to count uncovered squares and their values
         2) Calculate enhanced probability metrics for one die vs two dice that
            account for the value of covering multiple squares with one roll
         3) Evaluate strategic factors focusing on remaining low/mid squares
         4) Make a decision based on maximizing expected value and coverage potential
         5) Generate a detailed explanation of the reasoning
Reference: AI
********************************************************************* */
std::pair<int, std::string> Player::getOptimalDiceRollWithReason() const {
    // Count uncovered squares in range 1-6 only
    int totalUncovered = 0;
    // Squares 1-4
    int lowValueUncovered = 0;
    // Squares 5-6
    int midValueUncovered = 0;
    std::vector<int> uncoveredValues;

    // Only analyze squares 1-6 since 7-n must be covered to have dice choice
    int analysisBound = std::min(6, static_cast<int>(squares.size()));

    for (int i = 0; i < analysisBound; i++) {
        // Uncovered square
        if (squares[i] == 0) {
            totalUncovered++;
            int squareValue = i + 1;
            uncoveredValues.push_back(squareValue);

            if (squareValue <= 4) lowValueUncovered++;
            else midValueUncovered++;
        }
    }

    // Calculate progress for squares 1-6
    double progressPercentage = 100.0 * (analysisBound - totalUncovered) / analysisBound;



    // If only one square remains uncovered, favor precision of one die
    if (totalUncovered == 1) {
        return { 1, "Only one square remains uncovered (" +
                std::to_string(uncoveredValues[0]) +
                "). Rolling one die gives better precision for this specific value." };
    }

    // Define probability distributions
    // For one die: values 1-6 (equal probability of 1/6 each)
    const std::vector<double> oneDieProbs = { 0, 1 / 6.0, 1 / 6.0, 1 / 6.0, 1 / 6.0, 1 / 6.0, 1 / 6.0 };

    // For two dice: values 2-12
    const std::vector<double> twoDiceProbs = {
        // 0 and 1 (not possible)
        0, 0,                  
        // 2, 3
        1 / 36.0, 2 / 36.0,     
        //4. 5
        3 / 36.0, 4 / 36.0,
        // 6, 7
        5 / 36.0, 6 / 36.0,     
        // 8, 9
        5 / 36.0, 4 / 36.0,     
        // 10, 11
        3 / 36.0, 2 / 36.0,    
        // 12
        1 / 36.0                 
    };

    // Calculate expected values with enhanced metrics
    double oneDieExpectedValue = 0.0;
    double twoDiceExpectedValue = 0.0;

    // For one die (values 1-6)
    for (int i = 1; i <= 6; i++) {
        // Get all combinations that sum to i
        std::vector<std::vector<int>> combos = getCombinations(uncoveredValues, i);

        if (!combos.empty()) {
            // Find the best combination (most squares or highest total)
            int bestComboValue = 0;
            for (const auto& combo : combos) {
                // Value of a combo is a function of squares covered and their values
                // I give weight to both covering more squares and higher value squares
                // Base value for covering multiple squares is the 5
                int comboValue = combo.size() * 5;
                for (int square : combo) {
                    // Add actual square values
                    comboValue += square;
                }
                bestComboValue = std::max(bestComboValue, comboValue);
            }

            // Add to expected value (probability × value)
            oneDieExpectedValue += oneDieProbs[i] * bestComboValue;
        }
    }

    // For two dice (values 2-12)
    for (int i = 2; i <= 12; i++) {
        // Get all combinations that sum to i
        std::vector<std::vector<int>> combos = getCombinations(uncoveredValues, i);

        if (!combos.empty()) {
            // Find the best combination (most squares or highest total)
            int bestComboValue = 0;
            for (const auto& combo : combos) {
                // Value of a combo is a function of squares covered and their values
                // I give weight to both covering more squares and higher value squares
				// Base value for covering multiple squares is the 5
                int comboValue = combo.size() * 5;
                for (int square : combo) {
                    // Add actual square values
                    comboValue += square;
                }
                bestComboValue = std::max(bestComboValue, comboValue);
            }

            // Add to expected value (probability × value)
            twoDiceExpectedValue += twoDiceProbs[i] * bestComboValue;
        }
    }

    // Calculate usability percentages for reporting
    int oneUsableCounts = 0;
    for (int i = 1; i <= 6; i++) {
        if (!getCombinations(uncoveredValues, i).empty()) {
            oneUsableCounts++;
        }
    }
    double oneDieUsability = (oneUsableCounts / 6.0) * 100.0;

    // For two dice: count sum values we can utilize, weighted by probability
    double twoUsableWeight = 0.0;
    for (int i = 2; i <= 12; i++) {
        if (!getCombinations(uncoveredValues, i).empty()) {
            // Scale to 36 for integer comparison
            twoUsableWeight += twoDiceProbs[i] * 36.0;
        }
    }
    double twoDiceUsability = (twoUsableWeight / 36.0) * 100.0;

    // Decision factors
    std::string explanation;
    int decision;

    // Decision based on uncovered square configuration
    if (totalUncovered >= 4) {

        // With 4+ uncovered squares, lean towards 2 dice to cover more in one roll
        decision = 2;
        explanation = "With " + std::to_string(totalUncovered) +
            " uncovered squares remaining, two dice provide better coverage potential. " +
            "Expected value for two dice is significantly higher than for one die.";
    }
    // Decision based on uncovered square distribution
    else if (midValueUncovered > lowValueUncovered && midValueUncovered >= 2) {
        decision = 2;
        explanation = "More mid-value squares (" +
            std::to_string(midValueUncovered) +
            ") remain uncovered than low-value squares (" +
            std::to_string(lowValueUncovered) +
            "). Rolling two dice gives better chances for values 5-6.";
    }
    else if (lowValueUncovered >= totalUncovered / 2 && totalUncovered <= 2) {
        decision = 1;
        explanation = "Majority of uncovered squares (" +
            std::to_string(lowValueUncovered) + " out of " +
            std::to_string(totalUncovered) +
            ") are low-value (1-4) and few in number. One die provides better precision for these values.";
    }
    // Decision based on statistical expected value
      // 10% threshold for significance
    else if (twoDiceExpectedValue > oneDieExpectedValue * 1.1) {
        decision = 2;
        explanation = "Statistical analysis favors two dice with a higher expected value. " 
            "Two dice allow covering more squares in one roll.";
    }
    // 10% threshold for significance
    else if (oneDieExpectedValue > twoDiceExpectedValue * 1.1) {
        decision = 1;
        explanation = "Statistical analysis favors one die with a higher expected value. " 
            "One die provides more precise targeting.";
    }
    // Fall back to dice usability percentage if expected values are close
    else if (oneDieUsability > twoDiceUsability) {
        decision = 1;
        explanation = "One die offers " + std::to_string(static_cast<int>(oneDieUsability)) +
            "% chance of useful rolls vs " + std::to_string(static_cast<int>(twoDiceUsability)) +
            "% for two dice. One die is slightly advantageous.";
    }
    else {
        decision = 2;
        explanation = "Two dice offer " + std::to_string(static_cast<int>(twoDiceUsability)) +
            "% chance of useful rolls vs " + std::to_string(static_cast<int>(oneDieUsability)) +
            "% for one die. Two dice are slightly advantageous.";
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
Reference: AI
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
Reference: AI
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
Reference: AI
********************************************************************* */
bool Player::canUncoverSquare(int squareLabel, const Tournament* tournamentPtr) const {
    // Basic validation - square must be in range and covered
    if (squareLabel < 1 || squareLabel > squares.size()) return false;
    int idx = squareLabel - 1;

    // Already uncovered
    if (squares[idx] == 0) return false;

    // If no tournament pointer or handicap isn't active, no additional restrictions
    if (!tournamentPtr || !tournamentPtr->getHandicapActive()) return true;

    // Check if this is a handicap square
    if (squareLabel == tournamentPtr->getHandicapSquare() &&
        getName() == tournamentPtr->getAdvantagePlayerName() &&
        !hasHadTurnInRound) {

        // This is the handicap square for the advantage player who hasn't had a turn yet and you cannot uncover this protected square
        return false;
    }

    // Square can be uncovered
    return true;
}

/* *********************************************************************
Function Name: checkForceCovering
Purpose: Determines if the player must cover their own squares (cannot uncover)
Parameters:
         opponent      - a constant reference to the opponent Player object
         tournamentPtr - a pointer to the Tournament object for handicap info
         diceSum       - an integer representing the sum of dice
Return Value: true if covering is forced, false if uncovering is an option
Algorithm:
         1) Check if opponent has any covered squares
         2) Check for handicap protection
         3) Check if valid uncovering combinations exist
Reference: AI
********************************************************************* */
bool Player::checkForceCovering(const Player& opponent, const Tournament* tournamentPtr, int diceSum) const {

    // Rule 1: If opponent has no covered squares, cannot uncover
    bool opponentHasCoveredSquares = false;
    vector<int> oppSquares = opponent.getSquares();
    for (int sq : oppSquares) {

        // Opponent has covered at least one square
        if (sq != 0) {
            opponentHasCoveredSquares = true;
            break;
        }
    }
    if (!opponentHasCoveredSquares) {
        return true;
    }

    // Rule 2: Handicap protection
    bool handicapBlocking = tournamentPtr && tournamentPtr->getHandicapActive() &&
        opponent.getName() == tournamentPtr->getAdvantagePlayerName() &&
        !opponent.getHasHadTurnInRound();
    if (handicapBlocking) {
        return true;
    }

    // Rule 3: No valid combinations to uncover
    return !canUncover(diceSum, opponent, tournamentPtr);
}

/* *********************************************************************
Function Name: evaluateCoverMoves
Purpose: Evaluates all valid covering move combinations and selects the best one
Parameters:
         diceSum       - an integer representing the sum of dice
         coverDecision - reference to a MoveDecision structure to store the result
Return Value: None (modifies coverDecision by reference)
Algorithm:
         1) Find all valid cover combinations
         2) Score each combination based on strategic factors
         3) Select the highest-scoring combination
         4) Generate explanation for the selected move
Reference: AI
********************************************************************* */
void Player::evaluateCoverMoves(int diceSum, MoveDecision& coverDecision) {
    coverDecision.cover = true;
    coverDecision.squares.clear();

    // Find uncovered squares
    vector<int> myAvailable;
    for (int i = 0; i < static_cast<int>(squares.size()); i++) {
        if (squares[i] == 0)
            myAvailable.push_back(i + 1);
    }

    vector<vector<int>> coverCombos = getCombinations(myAvailable, diceSum);
    if (coverCombos.empty()) {
        return;
    }

    // Evaluate each cover combination
    int bestCoverScore = -1;
    string bestExplanation;

    for (const auto& combo : coverCombos) {

        // Skip empty combos (safety check)
        if (combo.empty()) continue;

        // Calculate score factors
        int comboSum = 0;
        int maxSquare = 0;
        int squareCount = combo.size();

        for (int square : combo) {
            comboSum += square;
            maxSquare = std::max(maxSquare, square);
        }

        // Base score calculation
        int score = comboSum + (2 * maxSquare);

        // Check if this move would win the game
        bool wouldWin = true;
        vector<int> simulatedBoard = squares;
        for (int sq : combo) {
            if (sq - 1 >= 0 && sq - 1 < static_cast<int>(simulatedBoard.size())) {

                // Mark as covered
                simulatedBoard[sq - 1] = sq;
            }
        }

        for (int val : simulatedBoard) {
            if (val == 0) {
                wouldWin = false;
                break;
            }
        }

        // Apply scoring bonuses
        if (wouldWin) {

			// Massive bonus for winning moves
            score += 1000;
        }
        if (maxSquare >= 7) {

			// Bonus for high-value squares
            score += 15;
        }
        else if (maxSquare >= 5) {

			// Bonus for mid-value squares
            score += 8;
        }
        if (squareCount > 1) {

			// Bonus for multiple squares
            score += squareCount * 3;
        }

        // Bonus for consecutive squares
        bool hasConsecutive = false;
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
            bestExplanation = generateMoveExplanation(combo, true, wouldWin);
        }
    }

    coverDecision.explanation = bestExplanation;
}

/* *********************************************************************
Function Name: evaluateUncoverMoves
Purpose: Evaluates all valid uncovering move combinations and selects the best one
Parameters:
         diceSum         - an integer representing the sum of dice
         opponent        - a constant reference to the opponent Player object
         tournamentPtr   - a pointer to the Tournament object for handicap info
         uncoverDecision - reference to a MoveDecision structure to store the result
Return Value: None (modifies uncoverDecision by reference)
Algorithm:
         1) Find all valid uncover combinations
         2) Score each combination based on strategic factors
         3) Select the highest-scoring combination
         4) Generate explanation for the selected move
Reference: AI
********************************************************************* */
void Player::evaluateUncoverMoves(int diceSum, const Player& opponent, const Tournament* tournamentPtr, MoveDecision& uncoverDecision) {
    uncoverDecision.cover = false;
    uncoverDecision.squares.clear();

    // If we can't uncover, return empty decision
    if (!canUncover(diceSum, opponent, tournamentPtr)) {
        return;
    }

    vector<int> oppCovered;
    vector<int> oppSquares = opponent.getSquares();

    // Check if handicap is active for filtering out the handicap square
    bool isHandicapActive = tournamentPtr && tournamentPtr->getHandicapActive() &&
        opponent.getName() == tournamentPtr->getAdvantagePlayerName() &&
        !opponent.getHasHadTurnInRound();
    int handicapSquare = isHandicapActive ? tournamentPtr->getHandicapSquare() : 0;

    // Only add squares that aren't protected by handicap
    for (int i = 0; i < static_cast<int>(oppSquares.size()); i++) {

		// Only consider covered squares
        if (oppSquares[i] != 0) {
            int squareLabel = i + 1;

            // Skip the handicap square if it's protected
            if (isHandicapActive && squareLabel == handicapSquare) {
                continue;
            }
            oppCovered.push_back(squareLabel);
        }
    }

    vector<vector<int>> uncoverCombos = getCombinations(oppCovered, diceSum);
    if (uncoverCombos.empty()) {
        return;
    }

    // Evaluate each uncover combination
    int bestUncoverScore = -1;
    string bestExplanation;

    for (const auto& combo : uncoverCombos) {

        // Skip empty combos (safety check)
        if (combo.empty()) continue;

        // Calculate score factors
        int comboSum = 0;
        int maxSquare = 0;
        int squareCount = combo.size();

        for (int square : combo) {
            comboSum += square;
            maxSquare = std::max(maxSquare, square);
        }

        // For uncovering, we generally want the lowest sum (most efficient) Base score: Lower sum is better
        int score = 30 - comboSum;

        // Check if this move would win the game
        bool wouldWin = true;
        vector<int> simulatedOpponentBoard = oppSquares;
        for (int sq : combo) {
            if (sq - 1 >= 0 && sq - 1 < static_cast<int>(simulatedOpponentBoard.size())) {

                // Mark as uncovered
                simulatedOpponentBoard[sq - 1] = 0;
            }
        }

        for (int val : simulatedOpponentBoard) {
            if (val != 0) {
                wouldWin = false;
                break;
            }
        }

        // Apply scoring bonuses
        if (wouldWin) {

            // Massive bonus for winning moves
            score += 1000;
        }
        if (maxSquare >= 7) {

            // Bonus for high-value squares
            score += 10;
        }
        if (squareCount > 1) {

			// Bonus for multiple squares
            score += squareCount * 2;
        }

        // Update best uncover decision if this is better
        if (score > bestUncoverScore) {
            bestUncoverScore = score;
            uncoverDecision.squares = combo;
            bestExplanation = generateMoveExplanation(combo, false, wouldWin);
        }
    }

    uncoverDecision.explanation = bestExplanation;
}

/* *********************************************************************
Function Name: makeStrategicDecision
Purpose: Decides between covering and uncovering based on strategic scoring
Parameters:
         coverDecision   - the best covering move decision
         uncoverDecision - the best uncovering move decision
         opponent        - a constant reference to the opponent Player object
Return Value: The strategically superior MoveDecision
Algorithm:
         1) If either move would win the game, prioritize it
         2) If both would win, calculate and compare potential scores
         3) Otherwise, use strategic scoring to compare the moves
         4) Return the superior move with enhanced explanation
Reference: AI
********************************************************************* */
MoveDecision Player::makeStrategicDecision(const MoveDecision& coverDecision,
    const MoveDecision& uncoverDecision,
    const Player& opponent) {

    // Check for win conditions
    vector<int> tempSquares = squares;
    bool coverWouldWin = false;
    bool uncoverWouldWin = false;

    // Check if cover move would win
    if (!coverDecision.squares.empty()) {
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
    }

    // Check if uncover move would win
    vector<int> tempOppSquares = opponent.getSquares();
    if (!uncoverDecision.squares.empty()) {
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
    }

    // If either move is a winning move, prioritize it
    if (coverWouldWin && !uncoverWouldWin) {
        MoveDecision result = coverDecision;
        //result.explanation = "Covering is recommended because it will win the game by covering all my squares. " + coverDecision.explanation;
        return result;
    }
    else if (!coverWouldWin && uncoverWouldWin) {
        MoveDecision result = uncoverDecision;
        //result.explanation = "Uncovering is recommended because it will win the game by uncovering all opponent's squares. " + uncoverDecision.explanation;
        return result;
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
            MoveDecision result = uncoverDecision;
            result.explanation = "Both moves would win the game, but uncovering yields a higher score (" +
                std::to_string(uncoverScore) + " vs " + std::to_string(coverScore) +
                "). " + uncoverDecision.explanation;
            return result;
        }
        else {
            MoveDecision result = coverDecision;
            result.explanation = "Both moves would win the game, but covering yields a higher score (" +
                std::to_string(coverScore) + " vs " + std::to_string(uncoverScore) +
                "). " + coverDecision.explanation;
            return result;
        }
    }

    // Neither move wins immediately - use enhanced strategic scoring
    if (coverDecision.squares.empty()) {
        return uncoverDecision;
    }
    if (uncoverDecision.squares.empty()) {
        return coverDecision;
    }

    // Calculate strategic scores
    int coverTotal = 0, uncoverTotal = 0, maxCover = 0, maxUncover = 0;

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

    int coverScore = coverTotal + (3 * maxCover);

    // Bonus for high-value squares
    if (maxCover >= 7) coverScore += 10;

    int uncoverScore = 30 - uncoverTotal + (2 * maxUncover);

    // Higher bonus for targeting opponent's high squares
    if (maxUncover >= 7) uncoverScore += 15;

    // Add bonus for multi-square moves
    coverScore += static_cast<int>(coverDecision.squares.size()) * 3;
    uncoverScore += static_cast<int>(uncoverDecision.squares.size()) * 2;

    // Make final decision with explanation
    if (uncoverScore > coverScore) {
        MoveDecision result = uncoverDecision;
        result.explanation = "Uncovering is recommended with strategic score " + std::to_string(uncoverScore) +
            " versus cover score " + std::to_string(coverScore) + ". " +
            uncoverDecision.explanation;
        return result;
    }
    else {
        MoveDecision result = coverDecision;
        result.explanation = "Covering is recommended with strategic score " + std::to_string(coverScore) +
            " versus uncover score " + std::to_string(uncoverScore) + ". " +
            coverDecision.explanation;
        return result;
    }
}

/* *********************************************************************
Function Name: generateMoveExplanation
Purpose: Generates a detailed explanation for a move decision
Parameters:
         combo    - vector of integers representing the chosen squares
         isCover  - boolean indicating if this is a cover (true) or uncover (false) move
         wouldWin - boolean indicating if this move would win the game
Return Value: a string containing the detailed explanation
Algorithm:
         1) Format the list of squares
         2) Generate appropriate explanation based on move type and square values
         3) Add special explanation for winning moves
Reference: AI
********************************************************************* */
std::string Player::generateMoveExplanation(const std::vector<int>& combo, bool isCover, bool wouldWin) {

    // Format the explanation intro
    string explanation;
    string moveType = isCover ? "Cover" : "Uncover";
    string verb = isCover ? "covers" : "targets";

    if (combo.size() == 1) {
        explanation = moveType + " square: " + formatNumberList(combo);
    }
    else {
        explanation = moveType + " squares: " + formatNumberList(combo);
    }

    // Add explanation details
    if (wouldWin) {
        if (isCover) {
            explanation += " because it would win the game by covering all squares!";
        }
        return explanation;
    }

    // For non-winning moves, provide strategic explanation
    if (combo.size() > 1) {

        // Sort squares by value to identify high and low values
        vector<int> sortedSquares = combo;
        std::sort(sortedSquares.begin(), sortedSquares.end());

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
                explanation += " because it " + verb + " the high-value square " +
                    std::to_string(highestSquare) +
                    " while " + (isCover ? "efficiently using" : "using") + " low-value square";

                // Add 's' if multiple low-value squares
                if (lowValueSquares.size() > 1) {
                    explanation += "s ";
                }
                else {
                    explanation += " ";
                }

                // Add all low-value squares
                explanation += formatNumberList(lowValueSquares);
                explanation += isCover ? "." : " to complete the combination.";

            }
            else if (highestSquare >= 7) {
                explanation += " because it " + verb + " high-value square " +
                    std::to_string(highestSquare) + ".";
            }
            else if (highestSquare >= 5) {

                // For mid-value square combinations
                if (combo.size() == 2) {
                    explanation += " because it " + (isCover ? "balances efficiency with strategic value by " + verb : "focuses on") +
                        " mid-value square " + std::to_string(highestSquare) + " along with square " +
                        std::to_string(sortedSquares.front()) +
                        (isCover ? "." : " to match the dice sum precisely.");
                }
                else if (combo.size() > 2) {
                    explanation += " because it strategically " + verb + " mid-value square " +
                        std::to_string(highestSquare) + " while " + (isCover ? "efficiently using" : "using") + " " +
                        std::to_string(combo.size() - 1) + " additional squares to match the " +
                        (isCover ? "dice sum." : "exact sum.");
                }
            }
            else if (combo.size() > 2) {
                explanation += " because it efficiently " + verb + " " + std::to_string(combo.size()) +
                    " squares to maximize " + (isCover ? "coverage" : "uncovering") + " with the given dice sum.";
            }
            else if (combo.size() == 2) {
                int firstSquare = sortedSquares.front();
                int secondSquare = sortedSquares.back();
                if (isCover) {
                    explanation += " because it uses the exact combination needed (" +
                        std::to_string(firstSquare) + " + " + std::to_string(secondSquare) +
                        " = " + std::to_string(firstSquare + secondSquare) +
                        ") to match the dice sum.";
                }
                else {
                    explanation += " because it specifically targets the combination of squares " +
                        std::to_string(firstSquare) + " and " + std::to_string(secondSquare) +
                        " which sum to " + std::to_string(firstSquare + secondSquare) +
                        ", matching the dice roll perfectly.";
                }
            }
        }
    }
    else if (combo.size() == 1) {

        // Single square case
        int square = combo[0];
        if (square >= 7) {
            explanation += " because it ";
            explanation += (isCover ? "is strategic as it covers" : "targets the");
            explanation += " high-value square ";
            explanation += std::to_string(square);
            explanation += ".";
        }
        else if (square >= 5) {
            explanation += " because it " + verb + " mid-value square " + std::to_string(square) +
                (isCover ? ", which provides good strategic value." : ", providing good tactical advantage.");
        }
        else {
            explanation += " because it " + verb + " a low-value square " + std::to_string(square) +
                ", which is " + (isCover ? "the best option for this dice roll." : "necessary given the current dice roll.");
        }
    }

    return explanation;
}

/* *********************************************************************
Function Name: decideMove
Purpose: To determine the player's move based on the dice roll and the opponent's board state.
Parameters:
         diceSum      - an integer representing the total from the dice roll
         opponent     - a constant reference to the opponent Player object
         allowUncover - a boolean flag indicating whether uncovering is allowed this turn
         tournamentPtr- a pointer to the Tournament object for handicap info
Return Value: A MoveDecision structure containing the decision (cover/uncover) and the chosen squares.
Algorithm:
         1) Check if covering is forced
         2) Evaluate the best covering move
         3) Evaluate the best uncovering move if allowed
         4) Make strategic decision between covering and uncovering
         5) Return the selected move with explanation
Reference: None
********************************************************************* */
MoveDecision Player::decideMove(int diceSum, const Player& opponent, bool allowUncover, const Tournament* tournamentPtr) {

    // Initialize move decisions
    MoveDecision coverDecision;
    coverDecision.cover = true;

    MoveDecision uncoverDecision;
    uncoverDecision.cover = false;

    // Check if covering is forced (cannot uncover)
    bool forceCovering = checkForceCovering(opponent, tournamentPtr, diceSum);

    // Step 1: Evaluate covering moves
    evaluateCoverMoves(diceSum, coverDecision);

    // Step 2: Evaluate uncovering moves if allowed
    if (!forceCovering && allowUncover) {
        evaluateUncoverMoves(diceSum, opponent, tournamentPtr, uncoverDecision);
    }

    // Step 3: Handle cases where only one type of move is available
    if (uncoverDecision.squares.empty() || forceCovering) {

        // No uncover move is available or covering is forced
        if (coverDecision.squares.empty()) {

            // No valid moves at all
            return MoveDecision{ true, vector<int>(), "No valid moves available for this dice sum." };
        }
        return coverDecision;
    }

    if (coverDecision.squares.empty()) {

        // Only an uncover move is available
        uncoverDecision.explanation = "Only an uncover move is available. " + uncoverDecision.explanation;
        return uncoverDecision;
    }

    // Step 4: Make strategic decision between covering and uncovering
    return makeStrategicDecision(coverDecision, uncoverDecision, opponent);
}