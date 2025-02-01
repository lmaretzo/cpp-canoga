/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#ifndef ROUND_H
#define ROUND_H

#include "Player.h"
#include "Dice.h"

// forward declarations
class Turn;

using namespace std;

class Round
{
public:
    Round(Player& p1, Player& p2, Dice& d, int boardSize);
    ~Round();

    // Conduct a single round
    // The round ends if someone covers all squares.
    void play();

private:
    Player& player1;
    Player& player2;
    Dice& dice;
    int boardSize;

    // Helper to check if the round is over
    bool isRoundOver() const;

    void determineFirstPlayer();

};

#endif
#pragma once
