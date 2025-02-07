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
********************************************************************* */
class Computer : public Player {
public:
    Computer(const string& name, int boardSize);
    virtual ~Computer();

    // Override chooseSquares to use the default AI strategy.
    virtual MoveDecision decideMove(int diceSum, const Player& opponent) override;
};

#endif
