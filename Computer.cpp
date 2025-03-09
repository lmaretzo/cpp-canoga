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

MoveDecision Computer::decideMove(int diceSum, const Player& opponent, bool allowUncover, const Tournament* tournamentPtr) {
    // Use the updated AI strategy from Player with tournament pointer
    MoveDecision decision = Player::decideMove(diceSum, opponent, allowUncover, tournamentPtr);

    // Added a delay to simulate "thinking"
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));


    // Convert explanation to past tense for computer's actions
    if (!decision.explanation.empty()) {
        // Replace phrases like "Covering squares" with "Covered squares"
        string pastTenseExplanation = decision.explanation;

        // Convert present tense to past tense
        if (decision.cover) {
            size_t pos = pastTenseExplanation.find("Cover squares");
            if (pos != string::npos) {
                pastTenseExplanation.replace(pos, 16, "Covered squares");
            }

            // Replace "is" with "was" for statements about the move
            pos = 0;
            while ((pos = pastTenseExplanation.find(" is ", pos)) != string::npos) {
                pastTenseExplanation.replace(pos, 4, " was ");
                pos += 5;
            }
        }
        else {
            size_t pos = pastTenseExplanation.find("Uncover squares");
            if (pos != string::npos) {
                pastTenseExplanation.replace(pos, 18, "Uncovered squares");
            }

            // Replace "targets" with "targeted" for statements about the move
            pos = 0;
            while ((pos = pastTenseExplanation.find(" targets ", pos)) != string::npos) {
                pastTenseExplanation.replace(pos, 9, " targeted ");
                pos += 10;
            }
        }

        cout << "Reasoning: " << pastTenseExplanation << "\n";
    }

    return decision;
}