#ifndef ROUND_H
#define ROUND_H

#include "Player.h"
#include "Dice.h"

// Forward declarations
class Turn;

using namespace std;

class Round
{
public:
    Round(Player& p1, Player& p2, Dice& d, int boardSize);
    ~Round();

    // Conduct a single round (basic version: each player gets one turn).
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
