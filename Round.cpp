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
    bothPlayersTurnComplete(false),
    firstTurnIsHuman(false),            // NEW: initialize to false
    roundWinner(nullptr),               // NEW: initialize pointers
    firstTurnPlayer(nullptr),
    winningScore(0)
{
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
        if (firstTurnIsHuman) {
            // Human goes first: assume player1 is Human, player2 is Computer.
            // Use the firstTurnForFirstPlayer flag:
            // If it's the first turn for player1, pass 'false' to disallow uncovering.
            // Otherwise, pass 'true'.
            Turn turnFirst(player1, player2, dice, firstTurnForFirstPlayer ? false : true);
            turnFirst.execute();

            // Now that player1 has taken a turn, update the flag.
            if (firstTurnForFirstPlayer) {
                firstTurnForFirstPlayer = false;
            }
            if (isRoundOver()) break;

            // Second player's turn always allows uncovering.
            Turn turnSecond(player2, player1, dice, true);
            turnSecond.execute();

            if (!bothPlayersTurnComplete) {
                bothPlayersTurnComplete = true;
            }
            // NEW: Immediately check for a win by uncovering
            if (bothPlayersTurnComplete && (player1.areAllUncovered() || player2.areAllUncovered())) {
                break;
            }

        }
        else {
            // Computer goes first: assume player2 is Computer, player1 is Human.
            Turn turnFirst(player2, player1, dice, false);
            turnFirst.execute();

            if (firstTurnForFirstPlayer) {
                firstTurnForFirstPlayer = false;
            }

            if (isRoundOver()) break;
            Turn turnSecond(player1, player2, dice, true);
            turnSecond.execute();
            if (!bothPlayersTurnComplete) {
                bothPlayersTurnComplete = true;
            }
            // NEW: Immediately check for a win by uncovering
            if (player1.areAllUncovered() || player2.areAllUncovered()) {
                break;
            }

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
        // Set flag based on player1’s type. (Assume that if name=="Human", then it's Human.)
        firstTurnIsHuman = (player1.getName() == "Human");
    }
    else if (sumP2 > sumP1)
    {
        cout << player2.getName() << " will go first!\n";
        // Swap players if player 2 should go first
        firstTurnIsHuman = (player2.getName() == "Human");

        //swap(player1, player2);
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