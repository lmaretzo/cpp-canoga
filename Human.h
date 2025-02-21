/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  Human Class Header
 ************************************************************/

#pragma once
#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include <string>
#include <vector>

using namespace std;

/* *********************************************************************
Class Name: Human
Purpose: To provide an implementation for a human-controlled player
         in the Canoga game. This class inherits from Player and overrides
         the decideMove method to prompt the user for input.
Parameters: None.
Return Value: None.
Algorithm: The decideMove method interacts with the user, offering hints
           if requested, forces covering when uncovering is not allowed, and
           validates the move input before returning the decision.
Reference: None
********************************************************************* */
class Human : public Player {
public:
    /* *********************************************************************
    Function Name: Human (Constructor)
    Purpose: To initialize a Human object with a given name and board size.
    Parameters:
         name       - a string representing the human player's name (passed by value)
         boardSize  - an integer representing the number of squares on the board
    Return Value: None.
    Algorithm: Calls the base class constructor to initialize player attributes.
    Reference: None
    ********************************************************************* */
    Human(const string& name, int boardSize);

    /* *********************************************************************
    Function Name: ~Human (Destructor)
    Purpose: To clean up any resources used by the Human object.
    Parameters: None.
    Return Value: None.
    Algorithm: Destructor performs any necessary cleanup. (No explicit cleanup required.)
    Reference: None
    ********************************************************************* */
    virtual ~Human();

    /* *********************************************************************
    Function Name: decideMove
    Purpose: To prompt the user for a move decision based on the dice roll and
             the opponent's board state.
    Parameters:
             diceSum      - an integer representing the total from the dice roll
             opponent     - a constant reference to the opponent Player object
             allowUncover - a boolean flag indicating whether the move may uncover
                            opponent's squares on this turn
    Return Value: A MoveDecision structure containing the user's decision (cover or uncover)
                 and the selected squares.
    Algorithm:
             1) Prompt the user to ask if they want a hint; if yes, display the hint.
             2) If allowUncover is false, force covering and notify the user.
             3) Otherwise, prompt the user to choose between covering and uncovering.
             4) Prompt the user to enter the squares for the move.
             5) Validate that the chosen squares sum to diceSum.
             6) Return the constructed MoveDecision.
    Reference: AI Assisted
    ********************************************************************* */
    virtual MoveDecision decideMove(int diceSum, const Player& opponent, bool allowUncover) override;
};

#endif
