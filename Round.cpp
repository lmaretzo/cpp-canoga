/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#include "Round.h"
#include "Turn.h"
#include <iostream>
#include "Tournament.h"
#include "Computer.h"

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
        firstTurnPlayer = player1;  // Set to Human if they went first
    }
    else
    {
        firstTurnPlayer = player2;  // Set to Computer if they went first
    }

    // Debugging Output to Ensure firstTurnPlayer is Assigned
    std::cout << "[DEBUG: firstTurnPlayer assigned]: "
        << (firstTurnPlayer ? firstTurnPlayer->getName() : "nullptr") << std::endl;
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
         1) Possibly determine the first-turn player by calling determineFirstPlayer(),
            unless skipFirstTurnRoll is true.
         2) Keep track that the first turn disallows uncovering for that player.
         3) Alternate turns until isRoundOver() returns true.
         4) Evaluate final win conditions and update scores.
         5) Store the first-turn player and show updated scores.
Reference: AI ASSISTED
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
        // ─────────────────────────────────────────────────────────
        // 1) BRAND-NEW ROUND (NOT SKIPPING FIRST TURN ROLL)
        // ─────────────────────────────────────────────────────────
        if (!skipFirstTurnRoll)
        {
            // === The code below is ORIGINAL logic ===
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
                Turn turnFirst(*player1, *player2, dice,
                    (firstTurnForFirstPlayer ? false : true),
                    tournamentPtr);
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
        // ─────────────────────────────────────────────────────────
        // 2) LOADED A MID-ROUND GAME (SKIPPING FIRST TURN ROLL)
        // ─────────────────────────────────────────────────────────
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



    // --- Evaluate final round outcomes: ---
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
Reference: None
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
********************************************************************* */
void Round::determineFirstPlayer()
{
    cin.clear();

    // Discard leftover characters (including newline) up to the next newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Rolling dice to determine who goes first...\n";

    auto rollP1 = dice.roll();
    auto rollP2 = dice.roll();

    int sumP1 = rollP1.first + rollP1.second;
    int sumP2 = rollP2.first + rollP2.second;

    cout << player1->getName() << " rolled " << rollP1.first
        << " and " << rollP1.second << " (sum = " << sumP1 << ")\n";
    cout << player2->getName() << " rolled " << rollP2.first
        << " and " << rollP2.second << " (sum = " << sumP2 << ")\n";

    // Handle tie as a recursive re-roll
    if (sumP1 == sumP2)
    {
        cout << "It's a tie! Re-rolling...\n";
        determineFirstPlayer();
        return;
    }

    // Non-tie: pick a winner
    if (sumP1 > sumP2)
    {
        cout << player1->getName() << " will go first!\n";
        firstTurnIsHuman = (player1->getName() == "Human");
        firstTurnPlayer = player1; // Now assigned correctly

    }
    else  // sumP2 > sumP1
    {
        cout << player2->getName() << " will go first!\n";
        firstTurnIsHuman = (player2->getName() == "Human");

        // swap so player1 always remains the "first" pointer
        std::swap(player1, player2);

        firstTurnPlayer = player1;


    }
    std::cout << "DEBUG First turn player is: " << firstTurnPlayer->getName() << std::endl;


    // *******************************************************
    //  Immediately update the tournament so mid-round save
    if (tournamentPtr)
    {
        tournamentPtr->setFirstTurnIsHuman(firstTurnIsHuman);
        // i do NOT call setNextTurn here,
        // because that might be decided later elsewhere.
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
    return *roundWinner; // roundWinner is a Player*
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
    return *firstTurnPlayer; // firstTurnPlayer is a Player*
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
