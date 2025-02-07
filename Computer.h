/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  (New) Computer Class Header
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
Purpose: Represents a computer-controlled player in the Canoga game.
         Inherits from Player and uses the default AI strategy.
Functions:
    - Computer(string name, int boardSize): Constructor.
    - ~Computer(): Destructor.
    - chooseSquares(int diceSum): Uses the default AI strategy to select squares.
Reference: Inherits default strategy from Player.
********************************************************************* */
class Computer : public Player {
public:
    Computer(const string& name, int boardSize);
    virtual ~Computer();

    // Override chooseSquares to use the default AI strategy.
    virtual MoveDecision decideMove(int diceSum) override;
};

#endif
