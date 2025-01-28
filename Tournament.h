#pragma once
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Player.h"
#include "Dice.h"

class Tournament
{
public:
    Tournament();
    ~Tournament();
    void enableManualDiceMode();
    void disableManualDiceMode();
    void start();

private:
    void initializeBoardSize();


    Player human;
    Player computer;
    Dice dice;
    int boardSize;
};

#endif
