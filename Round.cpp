/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#include "Round.h"
#include "Turn.h"
#include <iostream>

using namespace std;

/* *********************************************************************
Function Name: Round (Constructor)
Purpose: To initialize a Round object with two players, a dice object,
         and a board size. This constructor resets both players’ boards.
Parameters:
         p1         - a reference to the first Player object (by reference)
         p2         - a reference to the second Player object (by reference)
         d          - a reference to a Dice object (by reference)
         boardSize  - an integer representing the number of squares on the board
Return Value: None.
Algorithm:
         1) Initialize member variables with the given arguments.
         2) Set flags (bothPlayersTurnComplete, firstTurnIsHuman) to false.
         3) Set pointers (roundWinner, firstTurnPlayer) to nullptr.
         4) Reset the squares for both players using boardSize.
Reference: None
********************************************************************* */
Round::Round(Player& p1, Player& p2, Dice& d, int boardSize)
    : player1(p1), player2(p2), dice(d), boardSize(boardSize),
    bothPlayersTurnComplete(false),
    firstTurnIsHuman(false),            // Initialize first-turn flag to false.
    roundWinner(nullptr),               // Initialize roundWinner pointer.
    firstTurnPlayer(nullptr),           // Initialize firstTurnPlayer pointer.
    winningScore(0)                     // Initialize winningScore to 0.
{
    // Reset both players' boards.
    player1.resetSquares(boardSize);
    player2.resetSquares(boardSize);
}

/* *********************************************************************
Function Name: ~Round (Destructor)
Purpose: To clean up resources used by the Round object.
Parameters: None.
Return Value: None.
Algorithm:
         1) Destructor for Round; no explicit cleanup required.
Reference: None
********************************************************************* */
Round::~Round()
{
}

/* *********************************************************************
Function Name: play
Purpose: To execute a full round of the Canoga game. This function
         alternates turns between the two players until a win condition
         is met (either by covering all squares or uncovering all opponent squares).
Parameters: None.
Return Value: None.
Algorithm:
         1) Determine the first-turn player by calling determineFirstPlayer().
         2) Initialize a flag (firstTurnForFirstPlayer) to true.
         3) Loop until isRoundOver() returns true:
              a) If firstTurnIsHuman is true:
                 - Create a Turn for player1 with allowUncover set to false if firstTurnForFirstPlayer is true;
                   otherwise, allow uncovering.
                 - Execute the turn.
                 - Set firstTurnForFirstPlayer to false after player1’s first turn.
                 - Check for round over.
                 - Create and execute a Turn for player2 with allowUncover always true.
              b) Otherwise (if computer goes first):
                 - Similar logic applies, swapping the roles.
         4) After the loop, evaluate win conditions (cover win or uncover win) and update scores.
         5) Store the first-turn player and display updated scores.
Reference: AI ASSISTED
********************************************************************* */
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



    /* *********************************************************************
    Function Name: (Inline First Turn Storage)
    Purpose: To store the player who took the first turn in this round.
    Parameters: None.
    Return Value: None.
    Algorithm:
             1) Set firstTurnPlayer based on the outcome of determineFirstPlayer().
    Reference: AI ASSISTED
    ********************************************************************* */
    firstTurnPlayer = &player1; // or &player2 if applicable, based on your logic.

    // Display updated scores at the end of the round
    cout << "\n--- Updated Scores ---\n";
    cout << player1.getName() << ": " << player1.getScore() << "\n";
    cout << player2.getName() << ": " << player2.getScore() << "\n";
    // ai assistance code ends here


}

/* *********************************************************************
Function Name: isRoundOver
Purpose: To determine if the round has ended.
Parameters: None.
Return Value: A boolean value; true if the round is over, false otherwise.
Algorithm:
         1) If either player has all squares covered, return true.
         2) If both players have taken at least one turn and either player's board is all uncovered,
            return true.
         3) Otherwise, return false.
Reference: None
********************************************************************* */
bool Round::isRoundOver() const
{
    if (player1.areAllCovered() || player2.areAllCovered())
        return true;
    // Only check the uncover win condition if both players have taken at least one turn.
    if (bothPlayersTurnComplete && (player1.areAllUncovered() || player2.areAllUncovered()))
        return true;
    return false;
}

/* *********************************************************************
Function Name: determineFirstPlayer
Purpose: To decide which player takes the first turn by comparing dice rolls.
Parameters: None.
Return Value: None.
Algorithm:
         1) Both players roll the dice.
         2) Compute the sum of each roll.
         3) If one sum is greater than the other, that player is designated to go first.
         4) If the sums are equal, re-roll until a decision is reached.
Reference: None
********************************************************************* */
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
        // Set flag based on player1’s type. if name=="Human", then it's Human.
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