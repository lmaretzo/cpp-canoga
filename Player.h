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
    bool cover = true;       // Indicates if the move is to cover (true) or uncover (false)
    vector<int> squares;    // Holds the chosen squares for the move
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
    bool uncoverSquare(int squareLabel); 

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
    virtual MoveDecision decideMove(int diceSum, const Player& opponent, bool allowUncover);



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




private:
    string playerName; // Holds the player's name.
    //bool computer;
    int score; // Holds the player's current score.


    vector<int> squares;   // Represents the player's board; 0 indicates uncovered, non-zero indicates covered.
};

#endif
