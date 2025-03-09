/************************************************************
 * Name:     Lucas Maretzo
 * Project:  P1 Canoga
 * Class:    CMPS366 Operating Systems
 * Date:     3/10/2025
 ************************************************************/

#ifndef ROUND_H
#define ROUND_H

#include "Player.h"
#include "Dice.h"

class Turn;
class Tournament;

using namespace std;

/* *********************************************************************
Class Name: Round
Purpose: To manage a single round of the Canoga game, handling turn alternation,
         dice rolling, and determining the round winner.
Parameters: None.
Return Value: None.
Algorithm: Manages turn alternation between players until a win condition is met.
Reference: None
********************************************************************* */
class Round
{
public:
    /* *********************************************************************
    Function Name: Round (Constructor)
    Purpose: To initialize a Round object with two players, a dice object, and a board size.
             An additional flag indicates whether to reset the players' boards.
    Parameters:
             p1                   - reference to the first Player
             p2                   - reference to the second Player
             d                    - reference to the Dice object
             boardSize            - number of squares on the board
             resetBoards          - if true, reset the players' boards; if false, leave the board state intact
             tPtr                 - pointer to the Tournament object (optional)
             loadedFirstTurnIsHuman - flag indicating if human goes first when loading a game
             nextTurnStr          - string indicating whose turn is next when loading a game
             skipFirstTurnRoll    - flag indicating whether to skip the initial dice roll
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
        const std::string& nextTurnStr = "",
        bool skipFirstTurnRoll = false);

    /* *********************************************************************
    Function Name: ~Round (Destructor)
    Purpose: To clean up any resources associated with the Round object.
    Parameters: None.
    Return Value: None.
    Algorithm: No explicit cleanup required.
    Reference: None
    ********************************************************************* */
    ~Round();

    /* *********************************************************************
    Function Name: play
    Purpose: To execute a full round of the Canoga game, alternating turns between
             players until a win condition is met.
    Parameters: None.
    Return Value: None.
    Algorithm: Alternates turns between players, checks for win conditions, and
               calculates scores at the end of the round.
    Reference: None
    ********************************************************************* */
    void play();

    /* *********************************************************************
    Function Name: getRoundWinner
    Purpose: Returns a reference to the player who won the round.
    Parameters: None.
    Return Value: A reference to the winning Player.
    Algorithm: Returns the player stored in roundWinner.
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
    Player* player1;
    Player* player2;

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
    Data Member: roundWinner
    Purpose: Pointer to the player who won the round.
    ********************************************************************* */
    Player* roundWinner;

    /* *********************************************************************
    Data Member: firstTurnPlayer
    Purpose: Pointer to the player who took the first turn.
    ********************************************************************* */
    Player* firstTurnPlayer;

    /* *********************************************************************
    Data Member: winningScore
    Purpose: Score awarded to the winner of the round.
    ********************************************************************* */
    int winningScore;

    /* *********************************************************************
    Data Member: bothPlayersTurnComplete
    Purpose: Flag to track if both players have had at least one turn.
    ********************************************************************* */
    bool bothPlayersTurnComplete;

    /* *********************************************************************
    Data Member: firstTurnIsHuman
    Purpose: Flag indicating if the human player took the first turn.
    ********************************************************************* */
    bool firstTurnIsHuman;

    /* *********************************************************************
    Data Member: tournamentPtr
    Purpose: Pointer to the Tournament object for accessing game-wide settings.
    ********************************************************************* */
    Tournament* tournamentPtr;

    /* *********************************************************************
    Data Member: skipFirstTurnRoll
    Purpose: Flag to skip the initial dice roll when loading a saved game.
    ********************************************************************* */
    bool skipFirstTurnRoll;

    /* *********************************************************************
    Data Member: loadedNextTurn
    Purpose: Stores the next turn information for a loaded game.
    ********************************************************************* */
    std::string loadedNextTurn;

    /* *********************************************************************
    Function Name: isRoundOver
    Purpose: To check if the round has ended based on win conditions.
    Parameters: None.
    Return Value: A boolean value; true if the round is over, false otherwise.
    Algorithm: Checks if either player has covered all their squares or if all
               of a player's squares are uncovered after both have had turns.
    Reference: None
    ********************************************************************* */
    bool isRoundOver() const;

    /* *********************************************************************
    Function Name: determineFirstPlayer
    Purpose: To decide which player goes first by having each roll dice.
    Parameters: None.
    Return Value: None.
    Algorithm: Has each player roll dice and compares sums to determine who goes first.
               In case of a tie, players roll again.
    Reference: None
    ********************************************************************* */
    void determineFirstPlayer();
};

#endif