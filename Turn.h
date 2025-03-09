#ifndef TURN_H
#define TURN_H

#include "Player.h"
#include "Dice.h"

using namespace std;

class Tournament;

/* *********************************************************************
Class Name: Turn
Purpose: To manage a single turn in the Canoga game, handling dice rolling,
         move validation, and move execution for a player.
Parameters: None.
Return Value: None.
Algorithm: Manages the sequence of events in a player's turn, including
           dice rolls and move decisions.
Reference: None
********************************************************************* */
class Turn
{
public:
    /* *********************************************************************
    Function Name: Turn (Constructor)
    Purpose: To initialize a Turn object with the active player, the opponent,
             a reference to the dice object, and a flag indicating whether
             uncovering is allowed this turn.
    Parameters:
             activePlayer - a reference to the Player taking this turn
             opponent     - a reference to the opponent Player object
             dice         - a reference to the Dice object
             allowUncover - a boolean flag that is true if uncovering is allowed, false otherwise
             tPtr         - a pointer to the Tournament object (optional)
    Return Value: None.
    Algorithm:
             1) Initialize member variables with the given parameters.
             2) Set lastMoveWasUncover to false.
    Reference: None
    ********************************************************************* */
    Turn(Player& activePlayer, Player& opponent, Dice& dice, bool allowUncover = true, Tournament* tPtr = nullptr);

    /* *********************************************************************
    Function Name: execute
    Purpose: To execute the turn logic for the active player.
    Parameters: None.
    Return Value: None.
    Algorithm: Handles dice rolling, move decision, and move application.
    Reference: None
    ********************************************************************* */
    void execute();

private:
    /* *********************************************************************
    Data Member: player
    Purpose: Reference to the active player who is taking the current turn.
    ********************************************************************* */
    Player& player;

    /* *********************************************************************
    Data Member: opponent
    Purpose: Reference to the opponent player.
    ********************************************************************* */
    Player& opponent;

    /* *********************************************************************
    Data Member: diceRef
    Purpose: Reference to the dice object used for rolling dice during the turn.
    ********************************************************************* */
    Dice& diceRef;

    /* *********************************************************************
    Data Member: allowUncover
    Purpose: Flag indicating if uncovering opponent's squares is allowed this turn.
    ********************************************************************* */
    bool allowUncover;

    /* *********************************************************************
    Data Member: lastMoveWasUncover
    Purpose: Tracks whether the last move made was an uncover move.
    ********************************************************************* */
    bool lastMoveWasUncover;

    /* *********************************************************************
    Function Name: canCoverAnyCombination
    Purpose: To check whether there is any valid combination of uncovered squares
             on the given player's board that sum to the provided dice sum.
    Parameters:
             p   - a constant reference to the Player whose board is checked
             sum - an integer representing the dice sum
    Return Value: A boolean value; true if at least one valid combination exists, false otherwise.
    Algorithm: Examines all possible combinations of uncovered squares to find any that sum to the target.
    Reference: None
    ********************************************************************* */
    bool canCoverAnyCombination(const Player& p, int sum) const;

    /* *********************************************************************
    Function Name: areSquaresSevenToNCovered
    Purpose: To determine if squares numbered 7 through N on the player's board are all covered.
    Parameters:
             player - a constant reference to the Player whose board is checked
    Return Value: A boolean value; true if all squares from 7 to N are covered, false otherwise.
    Algorithm: Checks each square starting from index 6 (square 7) to see if any are uncovered.
    Reference: None
    ********************************************************************* */
    bool areSquaresSevenToNCovered(const Player& player) const;

    /* *********************************************************************
    Function Name: canUncoverAnyCombination
    Purpose: To check whether there is any valid combination of covered squares
             on the given player's board that sum to the provided dice sum.
    Parameters:
             p   - a constant reference to the Player whose board is checked
             sum - an integer representing the dice sum
    Return Value: A boolean value; true if at least one valid combination exists, false otherwise.
    Algorithm: Examines all possible combinations of covered squares to find any that sum to the target.
    Reference: None
    ********************************************************************* */
    bool canUncoverAnyCombination(const Player& p, int sum) const;

    /* *********************************************************************
    Data Member: tournamentPtr
    Purpose: Pointer to the Tournament object to access game-wide settings
             like handicap rules.
    ********************************************************************* */
    Tournament* tournamentPtr;
};

#endif