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

    // In Tournament.h (in the public section) for viewing debug in main:
    Player& getHuman() { return human; }
    Player& getComputer() { return computer; }
    bool getFirstTurnIsHuman() const { return firstTurnIsHuman; }
    std::string getNextTurn() const { return nextTurn; }



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

    // Serialization functions:
    bool saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);
private:
    void initializeBoardSize();
    void newGameInitialization();


    Player human;
    Player computer;
    Dice dice;
    int boardSize;

    // Handicap data members.
    int handicapSquare;         // Advantage square (0 if none)
    bool handicapActive;        // True if the advantage square is locked
    string advantagePlayerName; // Name of the player with the advantage

    std::string nextTurn;  // "Human" or "Computer"
    bool firstTurnIsHuman;
    bool gameLoaded;         // true if a game was successfully loaded from file
};
#endif
