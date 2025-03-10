/************************************************************
 * Name:     Lucas Maretzo
 * Project:  P1 Canoga
 * Class:    CMPS366 Operating Systems
 * Date:     3/10/2025
 ************************************************************/

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
Reference: AI 
********************************************************************* */
class Tournament
{
public:
    /* *********************************************************************
    Function Name: Tournament (Constructor)
    Purpose: Initializes a new Tournament object with default values.
    Parameters: None.
    Return Value: None.
    Algorithm: Sets up default values and initializes player objects.
    Reference: None
    ********************************************************************* */
    Tournament();

    /* *********************************************************************
    Function Name: ~Tournament (Destructor)
    Purpose: Cleans up resources used by the Tournament object.
    Parameters: None.
    Return Value: None.
    Algorithm: Performs necessary cleanup.
    Reference: None
    ********************************************************************* */
    ~Tournament();

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

    /* *********************************************************************
    Function Name: enableManualDiceMode
    Purpose: Enables the manual dice entry mode for testing.
    Parameters: None.
    Return Value: None.
    Algorithm: Calls the enableManualMode method on the dice object.
    Reference: None
    ********************************************************************* */
    void enableManualDiceMode();

    /* *********************************************************************
    Function Name: disableManualDiceMode
    Purpose: Disables the manual dice entry mode, reverting to random rolls.
    Parameters: None.
    Return Value: None.
    Algorithm: Calls the disableManualMode method on the dice object.
    Reference: None
    ********************************************************************* */
    void disableManualDiceMode();

    /* *********************************************************************
    Function Name: start
    Purpose: Starts and manages the tournament until completion.
    Parameters: None.
    Return Value: None.
    Algorithm: Sets up the game, plays rounds until the user decides to quit,
               applies handicap rules, and declares a winner.
    Reference: None
    ********************************************************************* */
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

    /* *********************************************************************
    Function Name: setHandicapSquare
    Purpose: Sets the handicap square value.
    Parameters:
             s - An integer representing the square number.
    Return Value: None.
    Algorithm: Assigns the parameter value to the handicapSquare member.
    Reference: None
    ********************************************************************* */
    void setHandicapSquare(int s) { handicapSquare = s; }

    /* *********************************************************************
    Function Name: setHandicapActive
    Purpose: Sets the handicap active status.
    Parameters:
             b - A boolean indicating if handicap should be active.
    Return Value: None.
    Algorithm: Assigns the parameter value to the handicapActive member.
    Reference: None
    ********************************************************************* */
    void setHandicapActive(bool b) { handicapActive = b; }

    /* *********************************************************************
    Function Name: setAdvantagePlayerName
    Purpose: Sets the name of the player with the handicap advantage.
    Parameters:
             name - A string with the player's name.
    Return Value: None.
    Algorithm: Assigns the parameter value to the advantagePlayerName member.
    Reference: None
    ********************************************************************* */
    void setAdvantagePlayerName(const std::string& name) { advantagePlayerName = name; }

    /* *********************************************************************
    Function Name: setFirstTurnIsHuman
    Purpose: Sets the flag indicating if the human player goes first.
    Parameters:
             val - A boolean indicating if the human goes first.
    Return Value: None.
    Algorithm: Assigns the parameter value to the firstTurnIsHuman member.
    Reference: None
    ********************************************************************* */
    void setFirstTurnIsHuman(bool val) { firstTurnIsHuman = val; }

    /* *********************************************************************
    Function Name: setNextTurn
    Purpose: Sets the next player's turn.
    Parameters:
             val - A string indicating whose turn is next ("Human" or "Computer").
    Return Value: None.
    Algorithm: Assigns the parameter value to the nextTurn member.
    Reference: AI
    ********************************************************************* */
    void setNextTurn(const std::string& val) { nextTurn = val; }

    /* *********************************************************************
    Function Name: saveGame
    Purpose: Saves the current game state to a file.
    Parameters:
             filename - A string representing the path to save the game.
    Return Value: A boolean indicating if the save was successful.
    Algorithm: Writes player states, scores, and turn information to the file.
    Reference: None
    ********************************************************************* */
    bool saveGame(const std::string& filename);

    /* *********************************************************************
    Function Name: loadGame
    Purpose: Loads a saved game state from a file.
    Parameters:
             filename - A string representing the path to load the game from.
    Return Value: A boolean indicating if the load was successful.
    Algorithm: Reads player states, scores, and turn information from the file.
    Reference: None
    ********************************************************************* */
    bool loadGame(const std::string& filename);

private:
    /* *********************************************************************
    Function Name: initializeBoardSize
    Purpose: Prompts the user to select a valid board size.
    Parameters: None.
    Return Value: None.
    Algorithm: Gets and validates user input for board size (9, 10, or 11).
    Reference: None
    ********************************************************************* */
    void initializeBoardSize();


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

    /* *********************************************************************
    Data Member: dice
    Purpose: Dice object used for rolling dice throughout the tournament.
    ********************************************************************* */
    Dice dice;

    /* *********************************************************************
    Data Member: boardSize
    Purpose: Stores the size of the game board (9, 10, or 11).
    ********************************************************************* */
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