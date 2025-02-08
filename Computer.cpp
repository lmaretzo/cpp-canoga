/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  Computer Class Implementation
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

MoveDecision Computer::decideMove(int diceSum, const Player& opponent, bool allowUncover) {
    // For now, simply use the default AI strategy from Player.
    MoveDecision decision = Player::decideMove(diceSum, opponent, allowUncover);

    // added a delay
    std::this_thread::sleep_for(std::chrono::milliseconds(2300));
    cout << getName() << " (Computer) has chosen squares: ";
    for (int sq : decision.squares)
        cout << sq << " ";
    cout << "\n";
    return decision;
}