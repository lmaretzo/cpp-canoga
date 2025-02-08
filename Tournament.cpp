/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/
#include "Tournament.h"
#include "Round.h"
#include <iostream>
#include "InputValidator.h"
#include "Human.h"
#include "Computer.h"

using namespace std;

/* *********************************************************************
Function Name: Tournament (Constructor)
Purpose: To initialize a Tournament object with default settings.
Parameters: None.
Return Value: None.
Algorithm:
         1) Set default board size to 9.
         2) Initialize handicapSquare to 0 and handicapActive flag to false.
Reference: None
********************************************************************* */
Tournament::Tournament()
    : boardSize(9), handicapSquare(0), handicapActive(false)
{
}


/* *********************************************************************
Function Name: ~Tournament (Destructor)
Purpose: To clean up resources used by the Tournament object.
Parameters: None.
Return Value: None.
Algorithm:
         1) Destructor; no explicit cleanup required.
Reference: None
********************************************************************* */
Tournament::~Tournament()
{
}

/* *********************************************************************
Function Name: initializeBoardSize
Purpose: To prompt the user to enter a valid board size (9, 10, or 11).
Parameters: None.
Return Value: None.
Algorithm:
         1) Prompt the user to input the board size.
         2) Validate input; if invalid, re-prompt until a valid size is entered.
Reference: None
********************************************************************* */
void Tournament::initializeBoardSize()
{
    cout << "Enter the board size (9, 10, or 11): ";
    while (true)
    {
        cin >> boardSize;
        if (boardSize >= 9 && boardSize <= 11)
            break;
        cout << "Invalid input. Please enter 9, 10, or 11: ";
    }
}

/* *********************************************************************
Function Name: start
Purpose: To run the tournament, playing multiple rounds until the user opts to stop.
Parameters: None.
Return Value: None.
Algorithm:
         1) Display a welcome message.
         2) Initialize board size by calling initializeBoardSize.
         3) Create Human and Computer player objects.
         4) Loop for each round:
              a) Create a new Round object and play the round.
              b) If a handicap is active, apply it to the appropriate player's board.
              c) Compute and apply handicap based on the previous round's outcome.
              d) Display current scores.
              e) Ask the user if they want to play another round.
         5) After rounds finish, display final scores and determine the tournament winner.
Reference: AI ASSISTED
********************************************************************* */
void Tournament::start()
{
    cout << "=== Welcome to Basic Canoga Game ===\n";
    cout << "We will play a few rounds until you decide to stop.\n";

    // Initialize board size based on user input
    initializeBoardSize();

    // Create the players using the chosen board size
    Human human("Human", boardSize);
    Computer  computer("Computer", boardSize);

    bool keepPlaying = true;
    while (keepPlaying)
    {
        // Create a Round and play it
        Round round(human, computer, dice, boardSize); // Pass boardSize to Round

        // --- NEW: Reapply handicap (if active) before the round starts ---
        if (getHandicapActive())
        {
            // Reapply the advantage square to the appropriate player's board.
            if (getAdvantagePlayerName() == human.getName())
                human.coverSquare(getHandicapSquare());
            else if (getAdvantagePlayerName() == computer.getName())
                computer.coverSquare(getHandicapSquare());
        }
        // ----------------------------------------------------------------

        round.play();

        // --- BEGIN HANDICAP CALCULATION BLOCK ---
        {
            // Retrieve round outcome data from the Round object.
            Player& winner = round.getRoundWinner();
            Player& firstTurn = round.getFirstTurnPlayer();
            int winScore = round.getWinningScore();

            // Compute the advantage square by summing the digits of the winning score.
            int advSquare = 0;
            int temp = winScore;
            while (temp > 0) {
                advSquare += temp % 10;
                temp /= 10;
            }

            // Determine which player receives the advantage.
            Player* advantagePlayer = nullptr;
            if (winner.getName() == firstTurn.getName()) {
                // Winner took first turn: advantage goes to the opponent.
                if (winner.getName() == human.getName())
                    advantagePlayer = &computer;
                else
                    advantagePlayer = &human;
            }
            else {
                // Winner did not take first turn: winner retains advantage.
                advantagePlayer = &winner;
            }

            // Apply the handicap: cover the advantage square on the advantage player's board.
            advantagePlayer->coverSquare(advSquare);


            // Store the handicap data in the Tournament instance.
            setHandicapSquare(advSquare);
            setAdvantagePlayerName(advantagePlayer->getName());
            setHandicapActive(true);

            // Output a message so the user sees that the handicap has been applied.
            cout << advantagePlayer->getName() << " has advantage with square "
                << advSquare << " locked.\n";
        }
        // --- END HANDICAP CALCULATION BLOCK ---

        // Show scores
        cout << "\nCurrent Scores:\n";
        cout << human.getName() << ": " << human.getScore() << "\n";
        cout << computer.getName() << ": " << computer.getScore() << "\n";

        // Ask the user if they want to play another round
        keepPlaying = InputValidator::getYesNo("\nPlay another round? (y/n): ");
    }

    // Display final scores and determine the winner
    cout << "\n=== Final Scores ===\n";
    cout << human.getName() << ": " << human.getScore() << "\n";
    cout << computer.getName() << ": " << computer.getScore() << "\n";

    if (human.getScore() > computer.getScore())
        cout << "=> Human wins the tournament!\n";
    else if (computer.getScore() > human.getScore())
        cout << "=> Computer wins the tournament!\n";
    else
        cout << "=> It's a draw!\n";

    cout << "Thank you for playing!\n";
}

/* *********************************************************************
Function Name: enableManualDiceMode
Purpose: To enable manual dice input mode for testing purposes.
Parameters: None.
Return Value: None.
Algorithm:
         1) Call dice.enableManualMode() on the dice object.
Reference: None
********************************************************************* */
void Tournament::enableManualDiceMode()
{
    dice.enableManualMode();
}

/* *********************************************************************
Function Name: disableManualDiceMode
Purpose: To disable manual dice input mode, reverting to random dice rolls.
Parameters: None.
Return Value: None.
Algorithm:
         1) Call dice.disableManualMode() on the dice object.
Reference: None
********************************************************************* */
void Tournament::disableManualDiceMode()
{
    dice.disableManualMode();
}
