/************************************************************
 * Name:     Lucas Maretzo
 * Project:  P1 Canoga
 * Class:    CMPS366 Operating Systems
 * Date:     3/10/2025
 ************************************************************/

#include "Round.h"
#include "Turn.h"
#include <iostream>
#include "Tournament.h"
#include "Computer.h"
#include <thread>
#include <chrono>

using namespace std;

/* *********************************************************************
Function Name: Round (Constructor)
Purpose: To initialize a Round object with two players, a dice object,
         and a board size. Resets both players' boards if resetBoards is true.
Parameters:
         p1         - reference to the first Player
         p2         - reference to the second Player
         d          - reference to the Dice object
         boardSize  - number of squares on the board
         resetBoards- if true, resets the players' boards; if false, leaves them unchanged
Return Value: None.
Algorithm:
         1) Initialize member variables.
         2) If resetBoards is true, call resetSquares(boardSize) on both players.
Reference: None
********************************************************************* */
Round::Round(
    Player& p1, 
    Player& p2, 
    Dice& d, 
    int boardSize,
    bool resetBoards, 
    Tournament* tPtr,
    bool loadedFirstTurnIsHuman,
    const std::string& nextTurnStr,
    bool skipFirstTurnRoll
)
    : player1(&p1),
    player2(&p2),
    dice(d),
    boardSize(boardSize),
    bothPlayersTurnComplete(false),
    firstTurnIsHuman(loadedFirstTurnIsHuman),
    roundWinner(nullptr),
    firstTurnPlayer(nullptr),
    winningScore(0),
    tournamentPtr(tPtr),
    skipFirstTurnRoll(skipFirstTurnRoll),
    loadedNextTurn(nextTurnStr) 


{
    if (resetBoards)
    {
        player1->resetSquares(boardSize);
        player2->resetSquares(boardSize);
    }

    // Reset the "has had turn" flags for both players
    player1->setHasHadTurnInRound(false);
    player2->setHasHadTurnInRound(false);


    // Ensure firstTurnPlayer is correctly assigned
    if (firstTurnIsHuman)
    {
        // Set to Human if they went first
        firstTurnPlayer = player1;
    }
    else
    {
        // Set to Computer if they went first
        firstTurnPlayer = player2;
    }


}

/* *********************************************************************
Function Name: ~Round (Destructor)
Purpose: To clean up resources used by the Round object.
Parameters: None.
Return Value: None.
Algorithm: No explicit cleanup required.
Reference: None
********************************************************************* */
Round::~Round()
{
}

/* *********************************************************************
Function Name: play
Purpose: To execute a full round of the Canoga game. This function
         alternates turns between the two players until a win condition
         is met (either by covering all squares or by uncovering all
         opponent squares).
Parameters: None.
Return Value: None.
Algorithm:
         1) If skipFirstTurnRoll is false, determine first player by rolling dice.
         2) For new rounds: Alternate turns starting with firstTurnPlayer, disallowing
            uncovering on the first turn only.
         3) For loaded games: Use loadedNextTurn to determine which player goes first,
            and toggle between Human and Computer for subsequent turns.
         4) Continue turns until isRoundOver() returns true.
         5) Evaluate final win conditions (all covered or all uncovered).
         6) Calculate and award scores to the winner.
         7) Update round outcome data and display the updated scores.
Reference: AI
********************************************************************* */
void Round::play()
{
    // If this is a brand-new round (no load mid-round), pick first turn by rolling dice:
    if (!skipFirstTurnRoll) {
        determineFirstPlayer();
    }

    // Tracks whether the first-turn player has had their initial turn
    bool firstTurnForFirstPlayer = true;

    // If we loaded a mid-round game, use loadedNextTurn to see who is up first:
    bool isHumanNext = (loadedNextTurn == "Human");

    // Keep taking turns until the round is over:
    while (!isRoundOver())
    {
        // 1) Brand-new round (not skipping turn roll)
        if (!skipFirstTurnRoll)
        {
            if (firstTurnIsHuman) {
                // First player's turn (Human)
                Turn turnFirst(*player1, *player2, dice,
                    (firstTurnForFirstPlayer ? false : true),
                    tournamentPtr);
                turnFirst.execute();
                if (firstTurnForFirstPlayer) {
                    firstTurnForFirstPlayer = false;
                }
                if (isRoundOver()) break;

                // Second player's turn (Computer), uncover always allowed
                Turn turnSecond(*player2, *player1, dice, true, tournamentPtr);
                turnSecond.execute();

                if (!bothPlayersTurnComplete) {
                    bothPlayersTurnComplete = true;
                }
                if (bothPlayersTurnComplete &&
                    (player1->areAllUncovered() || player2->areAllUncovered()))
                {
                    break;
                }
            }
            else {
                // First player's turn (Computer)
                Turn turnFirst(*player1, *player2, dice, true, tournamentPtr);
                turnFirst.execute();
                if (firstTurnForFirstPlayer) {
                    firstTurnForFirstPlayer = false;
                }
                if (isRoundOver()) break;

                // Second player's turn (Human)
                Turn turnSecond(*player2, *player1, dice, true, tournamentPtr);
                turnSecond.execute();

                if (!bothPlayersTurnComplete) {
                    bothPlayersTurnComplete = true;
                }
                if (bothPlayersTurnComplete &&
                    (player1->areAllUncovered() || player2->areAllUncovered()))
                {
                    break;
                }
            }
        }

        // 2) Loaded a mid-game round (Skipped first round)
        else
        {
            if (isHumanNext)
            {
                // If "Next Turn" is Human, the human goes first in this cycle
                Player& humanRef = (player1->getName() == "Human") ? *player1 : *player2;
                Player& compRef = (player1->getName() == "Human") ? *player2 : *player1;

                // Human's turn
                Turn turnFirst(humanRef, compRef, dice,
                    (firstTurnForFirstPlayer ? false : true),
                    tournamentPtr);
                turnFirst.execute();
                if (firstTurnForFirstPlayer) {
                    firstTurnForFirstPlayer = false;
                }
                if (isRoundOver()) break;

                // Then computer's turn
                Turn turnSecond(compRef, humanRef, dice, true, tournamentPtr);
                turnSecond.execute();

                if (!bothPlayersTurnComplete) {
                    bothPlayersTurnComplete = true;
                }
                if (bothPlayersTurnComplete &&
                    (player1->areAllUncovered() || player2->areAllUncovered()))
                {
                    break;
                }
            }
            else
            {
                // If "Next Turn" is Computer, the computer goes first in this cycle
                Player& compRef = (player1->getName() == "Computer") ? *player1 : *player2;
                Player& humanRef = (player1->getName() == "Computer") ? *player2 : *player1;

                // Computer's turn
                Turn turnFirst(compRef, humanRef, dice,
                    (firstTurnForFirstPlayer ? false : true),
                    tournamentPtr);
                turnFirst.execute();
                if (firstTurnForFirstPlayer) {
                    firstTurnForFirstPlayer = false;
                }
                if (isRoundOver()) break;

                // Then human's turn
                Turn turnSecond(humanRef, compRef, dice, true, tournamentPtr);
                turnSecond.execute();

                if (!bothPlayersTurnComplete) {
                    bothPlayersTurnComplete = true;
                }
                if (bothPlayersTurnComplete &&
                    (player1->areAllUncovered() || player2->areAllUncovered()))
                {
                    break;
                }
            }
            // Toggle for the next iteration of the loop
            isHumanNext = !isHumanNext;
        }
    }



    // Evaluate final round outcomes
    if (player1->areAllCovered()) {
        cout << "\n** " << player1->getName()
            << " covers all squares and wins the round! **\n";
        int scoreToAdd = 0;
        vector<int> oppSquares = player2->getSquares();
        for (size_t i = 0; i < oppSquares.size(); i++) {
            if (oppSquares[i] == 0) {
                scoreToAdd += (i + 1);
            }
        }
        player1->addToScore(scoreToAdd);
        cout << player1->getName() << " is awarded "
            << scoreToAdd << " points.\n";
        roundWinner = player1;
        winningScore = scoreToAdd;
    }
    else if (player2->areAllCovered()) {
        cout << "\n** " << player2->getName()
            << " covers all squares and wins the round! **\n";
        int scoreToAdd = 0;
        vector<int> oppSquares = player1->getSquares();
        for (size_t i = 0; i < oppSquares.size(); i++) {
            if (oppSquares[i] == 0) {
                scoreToAdd += (i + 1);
            }
        }
        player2->addToScore(scoreToAdd);
        cout << player2->getName() << " is awarded "
            << scoreToAdd << " points.\n";
        roundWinner = player2;
        winningScore = scoreToAdd;
    }
    else if (bothPlayersTurnComplete && player1->areAllUncovered()) {

        // Opponent uncovered all of player1's squares
        cout << "\n** " << player2->getName()
            << " uncovers all of " << player1->getName()
            << "'s squares and wins the round! **\n";
        int scoreToAdd = 0;
        vector<int> p2Squares = player2->getSquares();

        for (size_t i = 0; i < p2Squares.size(); i++) {

            // sum up your own covered squares
            if (p2Squares[i] != 0) {
                scoreToAdd += p2Squares[i];
            }
        }

        player2->addToScore(scoreToAdd);
        cout << player2->getName() << " is awarded "
            << scoreToAdd << " points.\n";
        roundWinner = player2;
        winningScore = scoreToAdd;
    }

    else if (bothPlayersTurnComplete && player2->areAllUncovered()) {
        // Opponent uncovered all of player2's squares
        cout << "\n** " << player1->getName()
            << " uncovers all of " << player2->getName()
            << "'s squares and wins the round! **\n";
        int scoreToAdd = 0;
        vector<int> p1Squares = player1->getSquares();
        for (size_t i = 0; i < p1Squares.size(); i++) {
            if (p1Squares[i] != 0) {
                scoreToAdd += p1Squares[i];
            }
        }

        player1->addToScore(scoreToAdd);
        cout << player1->getName() << " is awarded "
            << scoreToAdd << " points.\n";
        roundWinner = player1;
        winningScore = scoreToAdd;
    }


    // Display updated scores
    cout << "\n--- Updated Scores ---\n";
    cout << player1->getName() << ": " << player1->getScore() << "\n";
    cout << player2->getName() << ": " << player2->getScore() << "\n";
}

/* *********************************************************************
Function Name: isRoundOver
Purpose: Checks if the round has ended.
Parameters: None.
Return Value: true if the round is over, false otherwise.
Algorithm:
    1) If either player is fully covered, the round is over.
    2) If both players have had at least one turn and either
       player's board is all uncovered, the round is over.
    3) Otherwise, continue.
Reference: AI
********************************************************************* */
bool Round::isRoundOver() const
{
    // If a player's board is fully covered, that is a win
    if (player1->areAllCovered() || player2->areAllCovered())
        return true;

    // For an uncover win, check only if both players have had a turn
    if (bothPlayersTurnComplete)
    {
        if ((player1->isBoardModified() && player1->areAllUncovered()) ||
            (player2->isBoardModified() && player2->areAllUncovered()))
        {
            return true;
        }
    }
    return false;
}

/* *********************************************************************
Function Name: determineFirstPlayer
Purpose: Rolls dice for each player and decides who goes first, then
         updates the Tournament object immediately so mid-round saves
         reflect the correct "first turn" data.
Parameters: None
Return Value: None
Algorithm:
         1) Announce that players will roll to determine who goes first
         2) Have player1 roll first with a clear announcement
         3) Short pause for readability
         4) Have player2 roll second with a clear announcement
         5) Compare rolls and determine who goes first
         6) In case of tie, recursively re-roll
         7) If player2 goes first, swap player pointers
         8) Update Tournament object with first turn information
Reference: AI
********************************************************************* */
void Round::determineFirstPlayer()
{
    cout << "\n=== Determining First Player ===\n";
    cout << "Rolling dice to determine who goes first...\n";

    // First player rolls
    cout << "\n" << player1->getName() << " is rolling the dice...\n";
    auto rollP1 = dice.roll();
    int sumP1 = rollP1.first + rollP1.second;
    cout << player1->getName() << " rolled " << rollP1.first
        << " and " << rollP1.second << " (sum = " << sumP1 << ")\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Second player rolls
    cout << "\n" << player2->getName() << " is rolling the dice...\n";
    auto rollP2 = dice.roll();
    int sumP2 = rollP2.first + rollP2.second;
    cout << player2->getName() << " rolled " << rollP2.first
        << " and " << rollP2.second << " (sum = " << sumP2 << ")\n";

    // Handle tie as a recursive re-roll
    if (sumP1 == sumP2)
    {
        cout << "\nIt's a tie! Re-rolling...\n";
        determineFirstPlayer();
        return;
    }

    // Non-tie: pick a winner
    if (sumP1 > sumP2)
    {
        cout << "\n" << player1->getName() << " rolled higher and will go first!\n";
        firstTurnIsHuman = (player1->getName() == "Human");
        firstTurnPlayer = player1; // Now assigned correctly
    }
    else  // sumP2 > sumP1
    {
        cout << "\n" << player2->getName() << " rolled higher and will go first!\n";
        firstTurnIsHuman = (player2->getName() == "Human");

        // swap so player1 always remains the "first" pointer
        std::swap(player1, player2);

        firstTurnPlayer = player1;
    }

    // Update the tournament object with first turn information for mid-round saving
    if (tournamentPtr)
    {
        tournamentPtr->setFirstTurnIsHuman(firstTurnIsHuman);
        // I do not call setNextTurn here, because that might be decided later elsewhere.
    }
}


/* *********************************************************************
Function Name: getRoundWinner
Purpose: Returns a reference to the player who won the round.
Parameters: None.
Return Value: A reference to the winning Player.
Algorithm:
    1) Return roundWinner (dereferenced).
Reference: None
********************************************************************* */
Player& Round::getRoundWinner()
{
    // roundWinner is a Player*
    return *roundWinner;
}

/* *********************************************************************
Function Name: getFirstTurnPlayer
Purpose: Returns a reference to the player who took the first turn.
Parameters: None.
Return Value: A reference to the first-turn Player.
Algorithm:
    1) Return firstTurnPlayer (dereferenced).
Reference: None
********************************************************************* */
Player& Round::getFirstTurnPlayer()
{
    // firstTurnPlayer is a Player*
    return *firstTurnPlayer;
}

/* *********************************************************************
Function Name: getWinningScore
Purpose: Returns the winning score from the round (sum of the opponent's uncovered squares).
Parameters: None.
Return Value: An integer representing the winning score.
Algorithm:
    1) Return the value of the winningScore member variable.
Reference: None
********************************************************************* */
int Round::getWinningScore()
{
    return winningScore;
}
