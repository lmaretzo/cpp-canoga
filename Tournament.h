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

    /* *********************************************************************
    Function Name: getHuman
    Purpose: Returns a reference to the human player.
    Parameters: None.
    Return Value: A reference to the human Player.
    Algorithm:
         1) Dereference the human pointer.
    Reference: None
    ********************************************************************* */
    Player& getHuman() { return *human; }

    /* *********************************************************************
    Function Name: getComputer
    Purpose: Returns a reference to the computer player.
    Parameters: None.
    Return Value: A reference to the computer Player.
    Algorithm:
         1) Dereference the computer pointer.
    Reference: None
    ********************************************************************* */
    Player& getComputer() { return *computer; }

    bool getFirstTurnIsHuman() const { return firstTurnIsHuman; }
    std::string getNextTurn() const { return nextTurn; }

    void enableManualDiceMode();
    void disableManualDiceMode();
    void start();

    // Getters for handicap data.
    int getHandicapSquare() const { return handicapSquare; }
    bool getHandicapActive() const { return handicapActive; }
    std::string getAdvantagePlayerName() const { return advantagePlayerName; }

    // Setters for handicap data.
    void setHandicapSquare(int s) { handicapSquare = s; }
    void setHandicapActive(bool b) { handicapActive = b; }
    void setAdvantagePlayerName(const std::string& name) { advantagePlayerName = name; }

    // Serialization functions:
    bool saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);
private:
    void initializeBoardSize();
    void newGameInitialization();

    /* *********************************************************************
    Data Member: human
    Purpose: Pointer to the human player.
    ********************************************************************* */
    Player* human;

    /* *********************************************************************
    Data Member: computer
    Purpose: Pointer to the computer player.
    ********************************************************************* */
    Player* computer;

    Dice dice;
    int boardSize;

    // Handicap data members.
    int handicapSquare;         // Advantage square (0 if none)
    bool handicapActive;        // True if the advantage square is locked
    std::string advantagePlayerName; // Name of the player with the advantage

    std::string nextTurn;  // "Human" or "Computer"
    bool firstTurnIsHuman;
    bool gameLoaded;         // true if a game was successfully loaded from file
};

#endif
