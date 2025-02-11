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
#include <fstream>
#include <sstream>
#include <cstdlib>   // for std::stoi

using namespace std;

/* *********************************************************************
Function Name: Tournament (Constructor)
Purpose: To initialize a Tournament object with default settings.
Parameters: None.
Return Value: None.
Algorithm:
    1) Set default board size, handicap data, and gameLoaded flag.
    2) Allocate the human and computer players using derived classes.
Reference: None
********************************************************************* */
Tournament::Tournament()
    : boardSize(9), handicapSquare(0), handicapActive(false), nextTurn("Human"),
    firstTurnIsHuman(false), gameLoaded(false)
{
    human = new Human("Human", boardSize);      // Allocate human player.
    computer = new Computer("Computer", boardSize);  // Allocate computer player.
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

// This function is used when starting a new game.
void Tournament::newGameInitialization()
{
    cout << "=== Welcome to Basic Canoga Game ===\n";
    cout << "We will play a few rounds until you decide to stop.\n";
    initializeBoardSize();
    // (Any other initialization code for a new game can go here.)
}


/* *********************************************************************
Function Name: saveGame
Purpose: To save the current game state (players’ boards, scores, and turn info) to a file.
Parameters:
    filename - the file to save the game state.
Return Value: true if successful, false otherwise.
Algorithm:
    1) Open the file.
    2) Write the computer’s state.
    3) Write the human’s state.
    4) Write round/turn info.
Reference: None
********************************************************************* */
bool Tournament::saveGame(const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error: Could not open file for saving game.\n";
        return false;
    }
    // Save Computer state:
    out << "Computer:" << std::endl;
    out << "   Squares:";
    for (int s : computer->getSquares()) {
        out << " " << s;
    }
    out << std::endl;
    out << "   Score: " << computer->getScore() << std::endl << std::endl;

    // Save Human state:
    out << "Human:" << std::endl;
    out << "   Squares:";
    for (int s : human->getSquares()) {
        out << " " << s;
    }
    out << std::endl;
    out << "   Score: " << human->getScore() << std::endl << std::endl;

    // Save round/turn info.
    out << "First Turn: " << (firstTurnIsHuman ? "Human" : "Computer") << std::endl;
    out << "Next Turn: " << nextTurn << std::endl;

    out.close();
    return true;
}



/* *********************************************************************
Function Name: loadGame
Purpose: To load a saved game state from a file.
Parameters:
    filename - the file from which to load the game state.
Return Value: true if successful, false otherwise.
Algorithm:
    1) Open the file.
    2) Load the computer’s board state and score.
    3) Load the human’s board state and score.
    4) Load round/turn info.
Reference: None
********************************************************************* */
bool Tournament::loadGame(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error: Could not open file for loading game.\n";
        return false;
    }
    std::string line;
    size_t pos = 0;
    int num;

    // --- Load Computer state ---
    std::getline(in, line);  // should be "Computer:"
    if (line.find("Computer:") == std::string::npos) {
        std::cerr << "Error: Expected 'Computer:' header.\n";
        return false;
    }
    computer->setName("Computer");  // Set the computer's name

    std::getline(in, line);  // "   Squares: ..."
    pos = line.find("Squares:");
    if (pos == std::string::npos) return false;
    std::istringstream issComp(line.substr(pos + 8));
    std::vector<int> compSquares;
    while (issComp >> num) {
        compSquares.push_back(num);
    }
    computer->setSquares(compSquares);

    std::getline(in, line);  // "   Score: <score>"
    pos = line.find("Score:");
    if (pos == std::string::npos) return false;
    int compScore = std::stoi(line.substr(pos + 6));
    computer->setScore(compScore);

    std::getline(in, line);  // empty line

    // --- Load Human state ---
    std::getline(in, line);  // should be "Human:"
    if (line.find("Human:") == std::string::npos) {
        std::cerr << "Error: Expected 'Human:' header.\n";
        return false;
    }
    human->setName("Human");  // Set the human's name

    std::getline(in, line);  // "   Squares: ..."
    pos = line.find("Squares:");
    if (pos == std::string::npos) return false;
    std::istringstream issHuman(line.substr(pos + 8));
    std::vector<int> humanSquares;
    while (issHuman >> num) {
        humanSquares.push_back(num);
    }
    human->setSquares(humanSquares);

    std::getline(in, line);  // "   Score: <score>"
    pos = line.find("Score:");
    if (pos == std::string::npos) return false;
    int humanScore = std::stoi(line.substr(pos + 6));
    human->setScore(humanScore);

    std::getline(in, line);  // empty line

    // --- Load Round/Turn info ---
    std::getline(in, line);  // "First Turn: <player>"
    pos = line.find("First Turn:");
    if (pos == std::string::npos) return false;
    std::string firstTurnStr = line.substr(pos + 11);
    firstTurnStr.erase(0, firstTurnStr.find_first_not_of(" \t"));
    firstTurnIsHuman = (firstTurnStr == "Human");

    std::getline(in, line);  // "Next Turn: <player>"
    pos = line.find("Next Turn:");
    if (pos == std::string::npos) return false;
    nextTurn = line.substr(pos + 10);
    nextTurn.erase(0, nextTurn.find_first_not_of(" \t"));

    in.close();
    std::cout << "Game loaded successfully from " << filename << ".\n";

    // Mark that a game was loaded so that start() uses the loaded state.
    gameLoaded = true;

    // Optionally, update boardSize from the loaded human squares:
    if (!humanSquares.empty())
        boardSize = humanSquares.size();

    return true;
}

/* *********************************************************************
Function Name: start
Purpose: To run the tournament, playing multiple rounds until the user opts
         to stop. When a saved game is resumed, the very first round uses the
         loaded board state; subsequent rounds clear the board.
Parameters: None.
Return Value: None.
Algorithm:
    1) Display a welcome message.
    2) If no saved game was loaded, initialize board size and reset the players’ boards.
       Otherwise, resume with the loaded state.
    3) Set a flag (resetBoardsForRound) that is false for the first round if resuming,
       then true for all subsequent rounds.
    4) In each round, construct a Round with the given reset flag.
    5) After the first round (if resumed), update the flag so that future rounds reinitialize.
    6) Play the round, apply handicap, update scores, and then ask if the user wishes to continue.
Reference: None
********************************************************************* */
void Tournament::start()
{
    cout << "=== Welcome to Canoga ===\n";

    // If no saved game was loaded, perform new game initialization.
    // Otherwise, resume the saved game.
    if (!gameLoaded)
    {
        initializeBoardSize();
        human->setName("Human");
        computer->setName("Computer");
        human->resetSquares(boardSize);
        computer->resetSquares(boardSize);
    }
    else
    {
        cout << "Resuming saved game...\n";
        // Optionally, update boardSize from loaded human board:
        if (!human->getSquares().empty())
            boardSize = human->getSquares().size();
    }

    // When resuming a saved game, we want the first round to keep the loaded state.
    // We'll use a flag "firstResumedRound" that is true if gameLoaded was true.
    bool firstResumedRound = gameLoaded;
    // And we determine the reset flag for the round: if resuming, do NOT reset for the first round.
    // For a new game, we always reset.
    bool resetBoardsForRound = !gameLoaded;

    bool keepPlaying = true;
    while (keepPlaying)
    {
        // For the first round after loading, if firstResumedRound is true, then
        // we want resetBoardsForRound to be false (to preserve the loaded board state).
        // For subsequent rounds, we want it true.
        if (firstResumedRound)
        {
            resetBoardsForRound = false;
        }
        else
        {
            resetBoardsForRound = true;
        }

        // Create a new Round object.
        // The Round constructor will call resetSquares() on both players only if resetBoardsForRound is true.
        Round round(*human, *computer, dice, boardSize, resetBoardsForRound);

        // After playing the first resumed round, update the flag.
        if (firstResumedRound)
        {
            firstResumedRound = false; // For subsequent rounds, we will reset the boards.
        }

        // --- Reapply handicap (if active) before the round starts ---
        if (getHandicapActive())
        {
            if (getAdvantagePlayerName() == human->getName())
                human->coverSquare(getHandicapSquare());
            else if (getAdvantagePlayerName() == computer->getName())
                computer->coverSquare(getHandicapSquare());
        }
        // ----------------------------------------------------------------

        round.play();

        // --- BEGIN HANDICAP CALCULATION BLOCK ---
        {
            Player& winner = round.getRoundWinner();
            Player& firstTurn = round.getFirstTurnPlayer();
            int winScore = round.getWinningScore();

            int advSquare = 0;
            int temp = winScore;
            while (temp > 0) {
                advSquare += temp % 10;
                temp /= 10;
            }

            Player* advantagePlayer = nullptr;
            if (winner.getName() == firstTurn.getName())
            {
                if (winner.getName() == human->getName())
                    advantagePlayer = computer;
                else
                    advantagePlayer = human;
            }
            else
            {
                advantagePlayer = &winner;
            }
            advantagePlayer->coverSquare(advSquare);

            setHandicapSquare(advSquare);
            setAdvantagePlayerName(advantagePlayer->getName());
            setHandicapActive(true);

            cout << advantagePlayer->getName() << " has advantage with square "
                << advSquare << " locked.\n";
        }
        // --- END HANDICAP CALCULATION BLOCK ---

        // Show current scores.
        cout << "\nCurrent Scores:\n";
        cout << human->getName() << ": " << human->getScore() << "\n";
        cout << computer->getName() << ": " << computer->getScore() << "\n";

        // Ask the user if they want to play another round.
        keepPlaying = InputValidator::getYesNo("\nPlay another round? (y/n): ");
    }

    // Display final scores and determine the tournament winner.
    cout << "\n=== Final Scores ===\n";
    cout << human->getName() << ": " << human->getScore() << "\n";
    cout << computer->getName() << ": " << computer->getScore() << "\n";

    if (human->getScore() > computer->getScore())
        cout << "=> Human wins the tournament!\n";
    else if (computer->getScore() > human->getScore())
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

