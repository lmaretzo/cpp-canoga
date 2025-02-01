#include "Round.h"
#include "Turn.h"
#include <iostream>

using namespace std;

Round::Round(Player& p1, Player& p2, Dice& d, int boardSize)
    : player1(p1), player2(p2), dice(d), boardSize(boardSize)
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
    // This is a minimal approach:
    // We'll have each player take exactly one turn in a loop
    // until either covers all squares or we decide to limit turns.

    determineFirstPlayer();


    while (!isRoundOver())
    {
        // Player1's turn
        {
            Turn turnP1(player1, player2, dice);
            turnP1.execute();
            if (isRoundOver()) break;
        }

        // Player2's turn
        {
            Turn turnP2(player2, player1, dice);
            turnP2.execute();
            if (isRoundOver()) break;
        }
    }

    // Determine which player has all squares covered, if any
    if (player1.areAllCovered())
    {
        cout << "\n** " << player1.getName() << " covers all squares and wins the round! **\n";

        // NEW: Calculate opponent's uncovered square sum
// FIXED: Properly loop through uncovered squares
        int scoreToAdd = 0;
        vector<int> oppSquares = player2.getSquares();
        for (size_t i = 0; i < oppSquares.size(); i++) // Use index correctly
        {
            if (oppSquares[i] == 0) // If uncovered
            {
                scoreToAdd += (i + 1); // Square labels are 1-based
            }
        }

        player1.addToScore(scoreToAdd);
        cout << player1.getName() << " is awarded " << scoreToAdd << " points.\n"; // Print correct score
    }
    else if (player2.areAllCovered())
    {
        cout << "\n** " << player2.getName() << " covers all squares and wins the round! **\n";

        // FIXED: Properly loop through uncovered squares
        int scoreToAdd = 0;
        vector<int> oppSquares = player1.getSquares();
        for (size_t i = 0; i < oppSquares.size(); i++) // Use index correctly
        {
            if (oppSquares[i] == 0) // If uncovered
            {
                scoreToAdd += (i + 1); // Square labels are 1-based
            }
        }

        player2.addToScore(scoreToAdd);
        cout << player2.getName() << " is awarded " << scoreToAdd << " points.\n"; // Print correct score
    }




    // new code starts here
    // Display updated scores at the end of the round
    cout << "\n--- Updated Scores ---\n";
    cout << player1.getName() << ": " << player1.getScore() << "\n";
    cout << player2.getName() << ": " << player2.getScore() << "\n";
    // new code ends here


}

bool Round::isRoundOver() const
{
    // Round ends if either player has all squares covered
    if (player1.areAllCovered() || player2.areAllCovered())
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