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
        // Create properly formatted list of chosen squares
        string squaresList = formatNumberList(decision.squares);

        // Start with a clear statement of what was done
        string pastTenseExplanation;

        if (decision.cover) {
            pastTenseExplanation = "Covered squares: " + squaresList;
        }
        else {
            pastTenseExplanation = "Uncovered squares: " + squaresList;
        }

        // Extract the reason portion from the original explanation
        size_t becausePos = decision.explanation.find(" because");
        if (becausePos != string::npos) {
            string reasonPart = decision.explanation.substr(becausePos);

            // Fix any tense issues in the reason part
            size_t coverPos = reasonPart.find(" covers ");
            while (coverPos != string::npos) {
                reasonPart.replace(coverPos, 8, " covered ");
                coverPos = reasonPart.find(" covers ", coverPos + 9);
            }

            size_t targetPos = reasonPart.find(" targets ");
            while (targetPos != string::npos) {
                reasonPart.replace(targetPos, 9, " targeted ");
                targetPos = reasonPart.find(" targets ", targetPos + 10);
            }

            size_t isPos = reasonPart.find(" is ");
            while (isPos != string::npos) {
                reasonPart.replace(isPos, 4, " was ");
                isPos = reasonPart.find(" is ", isPos + 5);
            }

            // Remove duplicate phrases that might appear
            size_t exactSumPos = reasonPart.find(" to reach the exact sum. to reach the exact sum");
            if (exactSumPos != string::npos) {
                reasonPart.replace(exactSumPos, 45, " to reach the exact sum");
            }

            // Add the fixed reason part
            pastTenseExplanation += reasonPart;
        }

        // Remove any recommendation language
        size_t recPos = pastTenseExplanation.find("is recommended");
        if (recPos != string::npos) {
            pastTenseExplanation.replace(recPos, 14, "was chosen");
        }

        cout << "Reasoning: " << pastTenseExplanation << "\n";
    }

    return decision;
}