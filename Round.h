/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#ifndef ROUND_H
#define ROUND_H

#include "Player.h"
#include "Dice.h"

// forward declarations
class Turn;

using namespace std;

class Round
{
public:
    Round(Player& p1, Player& p2, Dice& d, int boardSize);
    ~Round();

    // Conduct a single round
    // The round ends if someone covers all squares.
    void play();

    /* *********************************************************************
    Function Name: getRoundWinner
    Purpose: Returns a reference to the player who won the round.
    Parameters: None.
    Return Value: A reference to the winning Player.
    Algorithm: The winner is determined after the round ends.
    Reference: None
    ********************************************************************* */
    Player& getRoundWinner();

    /* *********************************************************************
    Function Name: getFirstTurnPlayer
    Purpose: Returns a reference to the player who took the first turn in the round.
    Parameters: None.
    Return Value: A reference to the first-turn Player.
    Algorithm: Determined in determineFirstPlayer().
    Reference: None
    ********************************************************************* */
    Player& getFirstTurnPlayer();

    /* *********************************************************************
    Function Name: getWinningScore
    Purpose: Returns the winning score from the round (sum of the opponent's uncovered squares).
    Parameters: None.
    Return Value: An integer representing the winning score.
    Algorithm: Calculated at round end.
    Reference: None
    ********************************************************************* */
    int getWinningScore();

private:
    Player& player1;
    Player& player2;
    Dice& dice;
    int boardSize;

    Player* roundWinner;
    Player* firstTurnPlayer;
    int winningScore;

    // NEW CODE: Flag to indicate if both players have taken at least one turn.
    bool bothPlayersTurnComplete; // NEW CODE

    // Helper to check if the round is over
    bool isRoundOver() const;

    void determineFirstPlayer();

};

#endif
