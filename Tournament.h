#pragma once
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Player.h"
#include "Dice.h"
#include <string>

/* *********************************************************************
Class Name: Tournament
Purpose: Manages the overall tournament, including player data, game rounds,
         handicap rules, and game state persistence.
Attributes:
         human                 - Pointer to the human player.
         computer              - Pointer to the computer player.
         dice                  - Dice object used in the tournament.
         boardSize             - The number of squares on the board.
         handicapSquare        - The handicap square given as an advantage.
         handicapActive        - Boolean flag indicating if handicap is active.
         advantagePlayerName   - Name of the player with the advantage.
         nextTurn              - String indicating the next player's turn.
         firstTurnIsHuman      - Boolean indicating if the first turn belongs to the human player.
         gameLoaded            - Boolean flag indicating if a game was loaded.
Reference: None
********************************************************************* */
class Tournament
{
public:
    Tournament();  // Constructor
    ~Tournament(); // Destructor

    /* *********************************************************************
    Function Name: getHuman
    Purpose: Retrieves the human player.
    Parameters: None.
    Return Value: A reference to the human Player.
    Algorithm:
         1) Dereference the human pointer and return it.
    Reference: None
    ********************************************************************* */
    Player& getHuman() { return *human; }

    /* *********************************************************************
    Function Name: getComputer
    Purpose: Retrieves the computer player.
    Parameters: None.
    Return Value: A reference to the computer Player.
    Algorithm:
         1) Dereference the computer pointer and return it.
    Reference: None
    ********************************************************************* */
    Player& getComputer() { return *computer; }

    /* *********************************************************************
    Function Name: getFirstTurnIsHuman
    Purpose: Retrieves the boolean indicating if the first turn belongs to the human player.
    Parameters: None.
    Return Value: A boolean value indicating if the first turn is the human player's.
    Algorithm:
         1) Return the value of firstTurnIsHuman.
    Reference: None
    ********************************************************************* */
    bool getFirstTurnIsHuman() const { return firstTurnIsHuman; }

    /* *********************************************************************
    Function Name: getNextTurn
    Purpose: Retrieves the player designated for the next turn.
    Parameters: None.
    Return Value: A string indicating the next player's turn ("Human" or "Computer").
    Algorithm:
         1) Return the nextTurn string.
    Reference: None
    ********************************************************************* */
    std::string getNextTurn() const { return nextTurn; }

    void enableManualDiceMode();
    void disableManualDiceMode();
    void start();

    /* *********************************************************************
    Function Name: getHandicapSquare
    Purpose: Retrieves the handicap square assigned in the game.
    Parameters: None.
    Return Value: An integer representing the handicap square.
    Algorithm:
         1) Return the handicapSquare value.
    Reference: None
    ********************************************************************* */
    int getHandicapSquare() const { return handicapSquare; }

    /* *********************************************************************
    Function Name: getHandicapActive
    Purpose: Retrieves the status of the handicap feature.
    Parameters: None.
    Return Value: A boolean indicating if the handicap is active.
    Algorithm:
         1) Return the handicapActive value.
    Reference: None
    ********************************************************************* */
    bool getHandicapActive() const { return handicapActive; }

    /* *********************************************************************
    Function Name: getAdvantagePlayerName
    Purpose: Retrieves the name of the player with the handicap advantage.
    Parameters: None.
    Return Value: A string representing the name of the advantage player.
    Algorithm:
         1) Return the advantagePlayerName string.
    Reference: None
    ********************************************************************* */
    std::string getAdvantagePlayerName() const { return advantagePlayerName; }

    void setHandicapSquare(int s) { handicapSquare = s; }
    void setHandicapActive(bool b) { handicapActive = b; }
    void setAdvantagePlayerName(const std::string& name) { advantagePlayerName = name; }

    void setFirstTurnIsHuman(bool val) { firstTurnIsHuman = val; }
    void setNextTurn(const std::string& val) { nextTurn = val; }

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

    /* *********************************************************************
    Data Member: handicapSquare
    Purpose: Stores the advantage square (0 if no handicap is active).
    ********************************************************************* */
    int handicapSquare;

    /* *********************************************************************
    Data Member: handicapActive
    Purpose: Indicates if the handicap feature is currently active.
    ********************************************************************* */
    bool handicapActive;

    /* *********************************************************************
    Data Member: advantagePlayerName
    Purpose: Stores the name of the player with the handicap advantage.
    ********************************************************************* */
    std::string advantagePlayerName;

    /* *********************************************************************
    Data Member: nextTurn
    Purpose: Stores the identifier for the next player's turn ("Human" or "Computer").
    ********************************************************************* */
    std::string nextTurn;

    /* *********************************************************************
    Data Member: firstTurnIsHuman
    Purpose: Boolean indicating if the human player goes first.
    ********************************************************************* */
    bool firstTurnIsHuman;

    /* *********************************************************************
    Data Member: gameLoaded
    Purpose: Boolean flag indicating if a game was successfully loaded from a file.
    ********************************************************************* */
    bool gameLoaded;
};

#endif