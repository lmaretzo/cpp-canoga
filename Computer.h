/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#pragma once
#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include <string>
#include <vector>

using namespace std;

/* *********************************************************************
Class Name: Computer
Purpose: To provide an implementation for a computer-controlled player
         in the Canoga game. This class inherits from Player and overrides
         the decideMove method to automatically determine moves using the
         default AI strategy.
Parameters: None.
Return Value: None.
Algorithm: Inherits all board and scoring management from Player; the
           decideMove method calculates valid move combinations and selects
           one based on built-in heuristics.
Reference: None
********************************************************************* */
class Computer : public Player {
public:
    /* *********************************************************************
  Function Name: Computer (Constructor)
  Purpose: To initialize a Computer object with a given name and board size.
  Parameters:
           name       - a string representing the computer player's name (passed by value)
           boardSize  - an integer representing the number of squares on the board
  Return Value: None.
  Algorithm: Calls the base class constructor to initialize common attributes.
  Reference: None
  ********************************************************************* */
    Computer(const string& name, int boardSize);
    /* *********************************************************************
Function Name: ~Computer (Destructor)
Purpose: To clean up any resources used by the Computer object.
Parameters: None.
Return Value: None.
Algorithm: Destructor performs any necessary cleanup. (No explicit cleanup required.)
Reference: None
********************************************************************* */
    virtual ~Computer();

    /* *********************************************************************
    Function Name: decideMove
    Purpose: To determine the move for the computer player based on the dice roll
             and the state of the opponent's board.
    Parameters:
             diceSum      - an integer representing the total of the dice roll
             opponent     - a constant reference to the opponent Player object
             allowUncover - a boolean flag indicating whether uncovering the opponent's
                            squares is allowed this turn
    Return Value: A MoveDecision structure containing the decision (cover/uncover)
                 and the selected squares.
    Algorithm: Uses built-in AI logic to compute valid combinations for covering
               or uncovering and returns the selected move.
    Reference: None
    ********************************************************************* */
    virtual MoveDecision decideMove(int diceSum, const Player& opponent, bool allowUncover, const Tournament* tournamentPtr = nullptr) override;
};

#endif
