/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  (New) Computer Class Implementation
 ************************************************************/

#include "Computer.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

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

MoveDecision Computer::decideMove(int diceSum) {
    // For now, let the computer always choose covering moves using the default strategy.
    MoveDecision decision = Player::decideMove(diceSum);
    decision.cover = true;  // Force covering for the computer.
    cout << getName() << " (Computer) has chosen squares: ";
    for (int sq : decision.squares)
        cout << sq << " ";
    cout << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    return decision;
}