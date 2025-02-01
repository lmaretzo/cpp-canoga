#ifndef TURN_H
#define TURN_H

#include "Player.h"
#include "Dice.h"

using namespace std;

class Turn
{
public:
    Turn(Player& activePlayer, Player& opponent, Dice& dice);

    // Executes the turn logic such as roll dice, cover/uncover squares, etc
    void execute();

private:
    Player& player;
    Player& opponent;
    Dice& diceRef;

    // no advanced AI or help yet
    bool coverSquares(int diceSum);
    bool canCoverAnyCombination(const Player& p, int sum) const;
    bool areSquaresSevenToNCovered(const Player& player) const;

};

#endif
#pragma once
