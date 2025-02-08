/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  (New) Human Class Header
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
Purpose: Represents a human player in the Canoga game.
         Inherits from Player and overrides the move selection strategy.
Functions:
    - Human(string name, int boardSize): Constructor.
    - ~Human(): Destructor.
    - chooseSquares(int diceSum): Prompts the user for input, with an option for a hint.
Reference: Inherits AI strategy from Player for hints.
********************************************************************* */
class Human : public Player {
public:
    Human(const string& name, int boardSize);
    virtual ~Human();

    // Override the virtual method to prompt for user input.
    virtual MoveDecision decideMove(int diceSum, const Player& opponent, bool allowUncover) override;
};

#endif
