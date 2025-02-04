/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  (New) Computer Class Implementation
 ************************************************************/

#include "Computer.h"
#include "Player.h"
#include <iostream>
#include <vector>

using namespace std;

/* *********************************************************************
Function Name: Computer (Constructor)
Purpose: Initializes a Computer object with a given name and board size.
Parameters:
    - name: The computer player's name.
    - boardSize: The number of squares on the board.
Return Value: None
Reference: Inherits from Player.
********************************************************************* */
Computer::Computer(const string& name, int boardSize)
    : Player(name, boardSize)
{
}

/* *********************************************************************
Function Name: ~Computer (Destructor)
Purpose: Cleans up a Computer object.
Parameters: None
Return Value: None
Reference: Inherits from Player.
********************************************************************* */
Computer::~Computer()
{
}

/* *********************************************************************
Function Name: chooseSquares
Purpose: Uses the default AI strategy from the base Player class to choose squares.
Parameters:
    - diceSum: The total of the dice roll.
Return Value: A vector of integers representing the chosen squares.
Reference: Overrides Player::chooseSquares.
********************************************************************* */
vector<int> Computer::chooseSquares(int diceSum) {
    vector<int> chosen = Player::chooseSquares(diceSum);
    cout << getName() << " (Computer) has chosen squares: ";
    for (int sq : chosen)
        cout << sq << " ";
    cout << "\n";
    return chosen;
}
