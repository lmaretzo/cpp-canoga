#ifndef TURN_H
#define TURN_H

#include "Player.h"
#include "Dice.h"

using namespace std;

// A Turn represents one player's rolling and covering squares until they can't.
// In this simplified version, we handle only one roll per Turn for demonstration.
// In a more complete version, the player can roll repeatedly until no moves are possible.

class Turn
{
public:
    Turn(Player& activePlayer, Player& opponent, Dice& dice);

    // Executes the turn logic (roll dice, cover/uncover squares, etc.)
    void execute();

private:
    Player& player;
    Player& opponent;
    Dice& diceRef;

    // For a minimal approach: ask the user which squares to cover/uncover 
    // that add up to the dice sum. (No advanced AI or help yet.)
    bool coverSquares(int diceSum);
    bool canCoverAnyCombination(const Player& p, int sum) const;

};

#endif
#pragma once
