#ifndef TURN_H
#define TURN_H

#include "Player.h"
#include "Dice.h"

using namespace std;

class Turn
{
public:
    Turn(Player& activePlayer, Player& opponent, Dice& dice, bool allowUncover = true);

    // Executes the turn logic such as roll dice, cover/uncover squares, etc
    void execute();

private:
    Player& player;
    Player& opponent;
    Dice& diceRef;

    bool allowUncover; // NEW CODE

    bool lastMoveWasUncover; // NEW CODE: Track whether the last move was an uncover move.

    // no advanced AI or help yet
    bool canCoverAnyCombination(const Player& p, int sum) const;
    bool areSquaresSevenToNCovered(const Player& player) const;

};

#endif
#pragma once
