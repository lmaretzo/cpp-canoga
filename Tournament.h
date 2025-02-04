#pragma once
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Player.h"
#include "Dice.h"
#include <string>

class Tournament
{
public:
    Tournament();
    ~Tournament();
    void enableManualDiceMode();
    void disableManualDiceMode();
    void start();

    // Getters for handicap data.
    int getHandicapSquare() const { return handicapSquare; }
    bool getHandicapActive() const { return handicapActive; }
    string getAdvantagePlayerName() const { return advantagePlayerName; }

    // Setters for handicap data.
    void setHandicapSquare(int s) { handicapSquare = s; }
    void setHandicapActive(bool b) { handicapActive = b; }
    void setAdvantagePlayerName(const string& name) { advantagePlayerName = name; }
private:
    void initializeBoardSize();


    Player human;
    Player computer;
    Dice dice;
    int boardSize;

    // Handicap data members.
    int handicapSquare;         // Advantage square (0 if none)
    bool handicapActive;        // True if the advantage square is locked
    string advantagePlayerName; // Name of the player with the advantage
};
#endif
