/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#include "Round.h"
#include "Turn.h"
#include <iostream>

using namespace std;

Round::Round(Player& p1, Player& p2, Dice& d, int boardSize)
    : player1(p1), player2(p2), dice(d), boardSize(boardSize), 
    bothPlayersTurnComplete(false) // NEW CODE: Initialize flag to false.
{
    // Reset both players' squares at start of round
    player1.resetSquares(boardSize);
    player2.resetSquares(boardSize);
}

Round::~Round()
{
}

void Round::play()
{
    determineFirstPlayer();

    //  Track if the first–turn player (always player1 after determineFirstPlayer)
    // has taken their first turn. On their first turn, uncover moves are disallowed.
    bool firstTurnForFirstPlayer = true; // 

    while (!isRoundOver())
    {
        // Player1's turn (first–turn player)
        {
            bool allowUncoverFlag = true;
            if (firstTurnForFirstPlayer) {
                allowUncoverFlag = false; // : Restrict uncovering on first turn for first–turn player.
            }
            Turn turnP1(player1, player2, dice, allowUncoverFlag); // : Pass the allowUncover flag.
            turnP1.execute();
            if (firstTurnForFirstPlayer) { // Mark that the first–turn player has now taken their turn.
                firstTurnForFirstPlayer = false; // 
            }
            if (isRoundOver()) break;
        }

        // Player2's turn (always allowed to uncover)
        {
            Turn turnP2(player2, player1, dice, true); // : Always allow uncovering for second–turn player.
            turnP2.execute();
            // NEW CODE: After player2's first turn, mark that both players have taken a turn.
            if (!bothPlayersTurnComplete) {
                bothPlayersTurnComplete = true; // NEW CODE
            }
            if (isRoundOver()) break;
        }
    }

    //  Updated win–evaluation logic to account for the uncover win condition.
    if (player1.areAllCovered())
    {
        cout << "\n** " << player1.getName() << " covers all squares and wins the round! **\n";
        int scoreToAdd = 0;
        vector<int> oppSquares = player2.getSquares();
        for (size_t i = 0; i < oppSquares.size(); i++)
        {
            if (oppSquares[i] == 0)
            {
                scoreToAdd += (i + 1);
            }
        }
        player1.addToScore(scoreToAdd);
        cout << player1.getName() << " is awarded " << scoreToAdd << " points.\n";
        roundWinner = &player1;
        winningScore = scoreToAdd;
    }
    else if (player2.areAllCovered())
    {
        cout << "\n** " << player2.getName() << " covers all squares and wins the round! **\n";
        int scoreToAdd = 0;
        vector<int> oppSquares = player1.getSquares();
        for (size_t i = 0; i < oppSquares.size(); i++)
        {
            if (oppSquares[i] == 0)
            {
                scoreToAdd += (i + 1);
            }
        }
        player2.addToScore(scoreToAdd);
        cout << player2.getName() << " is awarded " << scoreToAdd << " points.\n";
        roundWinner = &player2;
        winningScore = scoreToAdd;
    }
    // Check for uncover win condition.



    else if (bothPlayersTurnComplete && player1.areAllUncovered())
    {
        // If player1’s board is all uncovered then player2 has successfully uncovered them.
        cout << "\n** " << player2.getName() << " uncovers all of " << player1.getName() << "'s squares and wins the round! **\n";
        int scoreToAdd = 0;
        vector<int> player2Squares = player2.getSquares();
        for (size_t i = 0; i < player2Squares.size(); i++)
        {
            if (player2Squares[i] != 0) // Sum player's own covered squares
            {
                scoreToAdd += player2Squares[i];
            }
        }
        player2.addToScore(scoreToAdd);
        cout << player2.getName() << " is awarded " << scoreToAdd << " points.\n";
        roundWinner = &player2;
        winningScore = scoreToAdd;
    }
    else if (bothPlayersTurnComplete && player2.areAllUncovered())
    {
        // If player2’s board is all uncovered then player1 wins by uncovering.
        cout << "\n** " << player1.getName() << " uncovers all of " << player2.getName() << "'s squares and wins the round! **\n";
        int scoreToAdd = 0;
        vector<int> player1Squares = player1.getSquares();
        for (size_t i = 0; i < player1Squares.size(); i++)
        {
            if (player1Squares[i] != 0)
            {
                scoreToAdd += player1Squares[i];
            }
        }
        player1.addToScore(scoreToAdd);
        cout << player1.getName() << " is awarded " << scoreToAdd << " points.\n";
        roundWinner = &player1;
        winningScore = scoreToAdd;
    }

    //  Store the first-turn player (assumed to be player1 after potential swapping).
    firstTurnPlayer = &player1;



    // NEW: Store the first-turn player.
// (Assuming determineFirstPlayer() already selected the first-turn player.)
/* *********************************************************************
Function Name: (Inline First Turn Storage)
Purpose: Store the player who took the first turn in the round.
Parameters: None.
Return Value: None.
Algorithm:
    1) Set firstTurnPlayer based on the outcome from determineFirstPlayer().
Reference: None
********************************************************************* */
    firstTurnPlayer = &player1; // or &player2 if applicable, based on your logic.

    // Display updated scores at the end of the round
    cout << "\n--- Updated Scores ---\n";
    cout << player1.getName() << ": " << player1.getScore() << "\n";
    cout << player2.getName() << ": " << player2.getScore() << "\n";
    // ai assistance code ends here


}

bool Round::isRoundOver() const
{
    if (player1.areAllCovered() || player2.areAllCovered())
        return true;
    // Only check the uncover win condition if both players have taken at least one turn.
    if (bothPlayersTurnComplete && (player1.areAllUncovered() || player2.areAllUncovered()))
        return true;
    return false;
}

void Round::determineFirstPlayer()
{
    cout << "Rolling dice to determine who goes first...\n";

    // Both players roll the dice
    auto rollP1 = dice.roll();
    auto rollP2 = dice.roll();

    int sumP1 = rollP1.first + rollP1.second;
    int sumP2 = rollP2.first + rollP2.second;

    cout << player1.getName() << " rolled " << rollP1.first << " and " << rollP1.second
        << " (sum = " << sumP1 << ")\n";
    cout << player2.getName() << " rolled " << rollP2.first << " and " << rollP2.second
        << " (sum = " << sumP2 << ")\n";

    // Determine the first player
    if (sumP1 > sumP2)
    {
        cout << player1.getName() << " will go first!\n";
    }
    else if (sumP2 > sumP1)
    {
        cout << player2.getName() << " will go first!\n";
        // Swap players if player 2 should go first
        swap(player1, player2);
    }
    else
    {
        cout << "It's a tie! Re-rolling...\n";
        determineFirstPlayer(); // Recursive call for a tie
    }
}

/* *********************************************************************
Function Name: getRoundWinner
Purpose: Returns a reference to the player who won the round.
Parameters: None.
Return Value: A reference to the winning Player.
Algorithm:
    1) Return the player stored in roundWinner.
Reference: None
********************************************************************* */
Player& Round::getRoundWinner() {
    return *roundWinner;
}

/* *********************************************************************
Function Name: getFirstTurnPlayer
Purpose: Returns a reference to the player who took the first turn.
Parameters: None.
Return Value: A reference to the first-turn Player.
Algorithm:
    1) Return the player stored in firstTurnPlayer.
Reference: None
********************************************************************* */
Player& Round::getFirstTurnPlayer() {
    return *firstTurnPlayer;
}

/* *********************************************************************
Function Name: getWinningScore
Purpose: Returns the winning score of the round.
Parameters: None.
Return Value: An integer representing the winning score.
Algorithm:
    1) Return the value stored in winningScore.
Reference: None
********************************************************************* */
int Round::getWinningScore() {
    return winningScore;
}
