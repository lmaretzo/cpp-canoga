/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

 // Forward declaration
class Tournament;

using namespace std;

/* *********************************************************************
Structure Name: MoveDecision
Purpose: To encapsulate a player's move decision, indicating whether the move
         is a covering or uncovering move and specifying the squares chosen.
Attributes:
         cover   - a boolean that is true if the move is to cover squares, false if uncovering
         squares - a vector of integers listing the chosen squares (empty if no move)
Reference: None
********************************************************************* */
struct MoveDecision {
    bool cover = true;      // Indicates if the move is to cover (true) or uncover (false)
    vector<int> squares;    // Holds the chosen squares for the move
    string explanation;     // Holds a brief explanation for the move decision
};


/* *********************************************************************
Class Name: Player
Purpose: To represent a player in the Canoga game, managing the player's board,
         score, and available actions such as covering or uncovering squares.
Parameters: None.
Return Value: None.
Algorithm: Provides functions for board manipulation, score management, and
           a virtual function decideMove for move decision-making, which derived
           classes override.
Reference: None
********************************************************************* */
class Player
{
public:
    /* *********************************************************************
    Function Name: Player (Default Constructor)
    Purpose: To initialize a Player object with default values.
    Parameters: None.
    Return Value: None.
    Algorithm: Sets the player's name to "Unknown", score to 0, and initializes
               the board to 9 uncovered squares.
    Reference: None
    ********************************************************************* */
    Player();

    /* *********************************************************************
    Function Name: Player (Parameterized Constructor)
    Purpose: To initialize a Player object with a specified name and board size.
    Parameters:
             name       - a string representing the player's name (passed by value)
             boardSize  - an integer representing the number of squares on the board
    Return Value: None.
    Algorithm: Sets the player's name and score, then initializes the board using resetSquares.
    Reference: None
    ********************************************************************* */
    Player(const string& name, int boardSize);

    /* *********************************************************************
    Function Name: ~Player (Destructor)
    Purpose: To clean up any resources associated with the Player object.
    Parameters: None.
    Return Value: None.
    Algorithm: Destructor for proper cleanup. (No explicit cleanup required in this implementation.)
    Reference: None
    ********************************************************************* */
    ~Player();

    /* *********************************************************************
    Function Name: getName
    Purpose: To retrieve the player's name.
    Parameters: None.
    Return Value: A string representing the player's name.
    Algorithm: Returns the value of the playerName attribute.
    Reference: None
    ********************************************************************* */
    string getName() const;

    /* *********************************************************************
    Function Name: getScore
    Purpose: To retrieve the player's current score.
    Parameters: None.
    Return Value: An integer representing the player's score.
    Algorithm: Returns the value of the score attribute.
    Reference: None
    ********************************************************************* */
    int getScore() const;

    /* *********************************************************************
    Function Name: setName
    Purpose: To update the player's name.
    Parameters:
             name - a string representing the new player name (passed by value)
    Return Value: None.
    Algorithm: Sets the playerName attribute to the provided value.
    Reference: None
    ********************************************************************* */
    void setName(const string& name);
   // void setIsComputer(bool flag);

   /* *********************************************************************
   Function Name: addToScore
   Purpose: To add a specified number of points to the player's score.
   Parameters:
            points - an integer representing the points to add
   Return Value: None.
   Algorithm: Increments the score attribute by the provided points.
   Reference: None
   ********************************************************************* */
    void addToScore(int points);

    /* *********************************************************************
    Function Name: coverSquare
    Purpose: To mark a square on the player's board as covered.
    Parameters:
             squareLabel - an integer (1-based index) representing the square to cover
    Return Value: A boolean value (true if the operation was successful, false otherwise).
    Algorithm: If the specified square is uncovered (value 0), mark it as covered by setting its value to the square number.
    Reference: None
    ********************************************************************* */
    bool coverSquare(int squareLabel);   

    /* *********************************************************************
    Function Name: uncoverSquare
    Purpose: To mark a square on the player's board as uncovered.
    Parameters:
             squareLabel - an integer (1-based index) representing the square to uncover
    Return Value: A boolean value (true if the operation was successful, false otherwise).
    Algorithm: If the specified square is covered (non-zero), mark it as uncovered by setting its value to 0.
    Reference: None
    ********************************************************************* */
    bool uncoverSquare(int squareLabel, const Tournament* tournamentPtr = nullptr);

    /* *********************************************************************
    Function Name: areAllCovered
    Purpose: To determine if every square on the player's board is covered.
    Parameters: None.
    Return Value: A boolean value; true if all squares are covered, false otherwise.
    Algorithm: Iterates through the board and returns false if any square is uncovered (0).
    Reference: None
    ********************************************************************* */
    bool areAllCovered() const;   

    /* *********************************************************************
    Function Name: areAllUncovered
    Purpose: To determine if every square on the player's board is uncovered.
    Parameters: None.
    Return Value: A boolean value; true if all squares are uncovered, false otherwise.
    Algorithm: Iterates through the board and returns false if any square is covered (non-zero).
    Reference: None
    ********************************************************************* */
    bool areAllUncovered() const; 

    /* *********************************************************************
    Function Name: getSquares
    Purpose: To obtain a copy of the player's board.
    Parameters: None.
    Return Value: A vector of integers representing the current state of the board.
    Algorithm: Returns a copy of the squares vector.
    Reference: None
    ********************************************************************* */
    vector<int> getSquares() const;

    /* *********************************************************************
    Function Name: printBoard
    Purpose: To display the player's current board state in a formatted manner.
    Parameters: None.
    Return Value: None.
    Algorithm: Prints the board with borders; uncovered squares show their number and covered squares show 'X'.
    Reference: None
    ********************************************************************* */
    void printBoard() const; // Print the player's current board


    /* *********************************************************************
    Function Name: isBoardModified
    Purpose: To check if the board has been modified from its initial state.
    Parameters: None.
    Return Value: true if at least one square is covered, false otherwise.
    Algorithm:
     1) Return the value of boardModified.
    Reference: None
    ********************************************************************* */
    bool isBoardModified() const;

    /* *********************************************************************
    Function Name: optimalDiceRoll
    Purpose: To compute the optimal number of dice (1 or 2) to roll when squares
             7 through N are already covered. This heuristic evaluates the first six
             squares by counting the number of uncovered squares and computing their average value.
    Parameters: None.
    Return Value: An integer; returns 1 if one die is optimal, or 2 if two dice are optimal.
    Algorithm:
             1) Iterate over the first six squares (or all squares if board size < 6).
             2) Count the number of uncovered squares and compute the total of their positions.
             3) Compute the average uncovered value.
             4) If the average is above a chosen threshold (e.g., 4.0) or if few squares are uncovered,
                return 1; otherwise, return 2.
    Reference: ai assist
    ********************************************************************* */
    int optimalDiceRoll() const;


    /* *********************************************************************
    Function Name: canUncover
    Purpose: Determines if uncovering opponent squares is allowed based on
             opponent board state and handicap rules.
    Parameters:
             diceSum       - an integer representing the dice roll sum
             opponent      - a reference to the opponent player
             tournamentPtr - a pointer to the Tournament for handicap information
    Return Value: A boolean value; true if uncovering is allowed, false otherwise.
    Algorithm:
             1) Check if opponent has any covered squares
             2) Check for valid uncover combinations
             3) Check handicap protection
    Reference: None
    ********************************************************************* */
    bool canUncover(int diceSum, const Player& opponent, const Tournament* tournamentPtr = nullptr) const;

    /* *********************************************************************
    Function Name: offerHint
    Purpose: To offer a hint for the player's move. (Placeholder for future strategy logic.)
    Parameters: None.
    Return Value: None.
    Algorithm: Currently prints a message indicating that no hint is available.
    Reference: None
    ********************************************************************* */
    void offerHint();

    /* *********************************************************************
    Function Name: resetSquares
    Purpose: To initialize or reset the player's board to a specified size with all squares uncovered.
    Parameters:
             boardSize - an integer representing the number of squares on the board
    Return Value: None.
    Algorithm: Assigns a new vector of size boardSize with all values set to 0 to the squares attribute.
    Reference: None
    ********************************************************************* */
    void resetSquares(int boardSize); // Pass the board size to resetSquares

    // Add these in Player.h inside the Player class declaration:
    void setSquares(const std::vector<int>& newSquares);
    void setScore(int newScore);

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
    void setHasHadTurnInRound(bool value);

    /* *********************************************************************
    Function Name: getHasHadTurnInRound
    Purpose: Gets the flag indicating whether the player has had a turn in the current round.
    Parameters: None.
    Return Value: A boolean value (true if player has had a turn, false otherwise).
    Algorithm:
             1) Return the value of hasHadTurnInRound.
    Reference: None
    ********************************************************************* */
    bool getHasHadTurnInRound() const;

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
    bool canUncoverSquare(int squareLabel, const Tournament* tournamentPtr = nullptr) const;

    /* *********************************************************************
Function Name: getCombinations
Purpose: To obtain all valid combinations of numbers that sum to a target value.
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
    static vector<vector<int>> getCombinations(const vector<int>& available, int target);

    /* *********************************************************************
Function Name: decideMove
Purpose: To determine the player's move based on the dice roll and the opponent's board state.
Parameters:
         diceSum      - an integer representing the total from the dice roll
         opponent     - a constant reference to the opponent Player object
         allowUncover - a boolean flag indicating whether uncovering the opponent's squares is allowed this turn
Return Value: A MoveDecision structure that contains the decision (cover/uncover) and the chosen squares.
Algorithm: Computes valid move combinations and returns a decision; intended to be overridden by derived classes.
Reference: None
********************************************************************* */
    virtual MoveDecision decideMove(int diceSum, const Player& opponent, bool allowUncover, const Tournament* tournamentPtr = nullptr);

    // Add these method declarations to the Player class in Player.h

        /* *********************************************************************
        Function Name: getOptimalDiceRollWithReason
        Purpose: Determines the strategic choice between rolling one or two dice
                 with a detailed explanation of the reasoning process. This should only
                 be called when squares 7-n are covered (when player has a choice).
        Parameters: None.
        Return Value: A pair containing:
                      - an integer (1 or 2) representing the optimal number of dice to roll
                      - a string explaining the reasoning behind the decision
        Algorithm:
                 1) Analyze the full board state, considering all uncovered squares
                 2) Evaluate strategic factors like value distribution and game progress
                 3) Calculate probabilities of useful rolls for both one and two dice
                 4) Return the optimal decision with a detailed explanation
        Reference: None
        ********************************************************************* */
    std::pair<int, std::string> getOptimalDiceRollWithReason() const;

    /* *********************************************************************
    Function Name: canCoverSum
    Purpose: Helper method to check if there exists any combination of the given
             values that sums to the target value, respecting game rules.
    Parameters:
             values - a vector of integers representing available values
             target - an integer representing the sum to reach
    Return Value: Boolean indicating whether a valid combination exists.
    Algorithm:
             1) Check combinations of 1-4 elements that sum to the target
             2) Return true as soon as a valid combination is found
    Reference: None
    ********************************************************************* */
    bool canCoverSum(const std::vector<int>& values, int target) const;

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
    std::string formatNumberList(const std::vector<int>& numbers) const;
private:
    string playerName; // Holds the player's name.
    //bool computer;
    int score; // Holds the player's current score.


    vector<int> squares;   // Represents the player's board; 0 indicates uncovered, non-zero indicates covered.

    /* *********************************************************************
    Data Member: boardModified
    Purpose: Indicates whether the board has been modified during the round.
    ********************************************************************* */
    bool boardModified;
    bool hasHadTurnInRound; // Track if player has had a turn in the current round

    /* *********************************************************************
Function Name: findCombinations
Purpose: Helper method for getCombinations that recursively finds combinations.
Parameters:
         nums    - available numbers
         target  - desired sum
         start   - starting index
         current - current combination
         result  - storage for valid combinations
Return Value: None.
Reference: None
********************************************************************* */
    static void findCombinations(const vector<int>& nums, int target, int start,
        vector<int>& current, vector<vector<int>>& result);

};




#endif
