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
class Tournament;

using namespace std;

class Round
{
public:
    /* *********************************************************************
    Function Name: Round (Constructor)
    Purpose: To initialize a Round object with two players, a dice object, and a board size.
             An additional flag indicates whether to reset the players� boards.
    Parameters:
         p1         - reference to the first Player
         p2         - reference to the second Player
         d          - reference to the Dice object
         boardSize  - number of squares on the board
         resetBoards- if true, reset the players� boards; if false, leave the board state intact
    Return Value: None.
    Algorithm:
         1) Initialize member variables.
         2) If resetBoards is true, call resetSquares(boardSize) on both players.
    Reference: None
    ********************************************************************* */
    Round(
        Player& p1, 
        Player& p2, 
        Dice& d, 
        int boardSize, 
        bool resetBoards = true, 
        Tournament* tPtr = nullptr,
        bool loadedFirstTurnIsHuman = false, 
        const std::string& nextTurnStr = "", // RENAMED param
        bool skipFirstTurnRoll = false);

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
    /* *********************************************************************
    Data Member: player1, player2
    Purpose: Pointers to the two players participating in the round.
    ********************************************************************* */
    Player* player1;          // Pointer to first player
    Player* player2;          // Pointer to second player

    /* *********************************************************************
    Data Member: dice
    Purpose: Reference to the dice object used for rolling dice during the round.
    ********************************************************************* */
    Dice& dice;

    /* *********************************************************************
    Data Member: boardSize
    Purpose: Stores the number of squares on each player's board.
    ********************************************************************* */
    int boardSize;

    /* *********************************************************************
    Data Member: roundWinner, firstTurnPlayer, winningScore
    Purpose: Track round outcomes including which player won, who went first,
             and how many points were awarded.
    ********************************************************************* */
    Player* roundWinner;
    Player* firstTurnPlayer;
    int winningScore;

    /* *********************************************************************
    Data Member: bothPlayersTurnComplete, firstTurnIsHuman
    Purpose: Track game state flags for determining valid move options and
             win conditions.
    ********************************************************************* */
    bool bothPlayersTurnComplete;
    bool firstTurnIsHuman;

    /* *********************************************************************
    Data Member: tournamentPtr, skipFirstTurnRoll, loadedNextTurn
    Purpose: Manage game state with the tournament and handle saved games.
    ********************************************************************* */
    Tournament* tournamentPtr;
    bool skipFirstTurnRoll;
    std::string loadedNextTurn;


    // Helper to check if the round is over
    bool isRoundOver() const;

    void determineFirstPlayer();


};

#endif