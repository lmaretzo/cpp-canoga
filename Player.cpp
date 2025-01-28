#include "Player.h"
#include <iostream> // for debugging or printing in hint method

using namespace std;

Player::Player()
    : playerName("Unknown"), computer(false), score(0), squares(9, 0)
{
    // squares default to uncovered (all zero).
}

Player::Player(const string& name, bool isComp, int boardSize)
    : playerName(name), computer(isComp), score(0)
{
        resetSquares(boardSize);
}

void Player::resetSquares(int boardSize)
{
    squares.assign(boardSize, 0); // Reset squares dynamically based on the board size
}

Player::~Player()
{
    // nothing special
}

string Player::getName() const
{
    return playerName;
}

bool Player::isComputerPlayer() const
{
    return computer;
}

int Player::getScore() const
{
    return score;
}

void Player::setName(const string& name)
{
    playerName = name;
}

void Player::setIsComputer(bool flag)
{
    computer = flag;
}

void Player::addToScore(int points)
{
    score += points;
}



bool Player::coverSquare(int squareLabel)
{
    if (squareLabel < 1 || squareLabel > squares.size()) return false;
    int idx = squareLabel - 1;
    if (squares[idx] != 0)
    {
        // already covered
        return false;
    }
    squares[idx] = squareLabel; // now covered
    return true;
}

bool Player::uncoverSquare(int squareLabel)
{
    if (squareLabel < 1 || squareLabel > squares.size()) return false;
    int idx = squareLabel - 1;
    if (squares[idx] == 0)
    {
        // already uncovered
        return false;
    }
    squares[idx] = 0; // now uncovered
    return true;
}

bool Player::areAllCovered() const
{
    for (int val : squares)
    {
        if (val == 0) return false;
    }
    return true;
}

bool Player::areAllUncovered() const
{
    for (int val : squares)
    {
        if (val != 0) return false;
    }
    return true;
}

vector<int> Player::getSquares() const
{
    return squares; // return a copy
}

void Player::printBoard() const {
    cout << endl;
    cout << playerName << "'s Board:" << endl;

    // Generate the top border dynamically
    for (int i = 0; i < squares.size(); ++i) {
        cout << "+---";
    }
    cout << "+" << endl; // End the top border

    // Generate the row content dynamically
    for (int i = 0; i < squares.size(); ++i) {
        if (squares[i] == 0) {
            // Uncovered square shows its number
            if (i + 1 < 10) {
                cout << "| " << (i + 1) << " "; // Single-digit alignment
            }
            else {
                cout << "| " << (i + 1); // Double-digit alignment
            }
        }
        else {
            // Covered square shows "X"
            cout << "| X ";
        }
    }
    cout << "|" << endl; // End the row content

    // Generate the bottom border dynamically
    for (int i = 0; i < squares.size(); ++i) {
        cout << "+---";
    }
    cout << "+" << endl; // End the bottom border

    cout << endl;
}



void Player::offerHint()
{
    // Placeholder for future expansions (AI strategy, heuristics, etc.)
    cout << "[" << playerName << "] HINT: (Not yet implemented)\n";
}

// Add this at the end of Player.cpp

//void Player::resetSquares()
//{
//    squares.assign(squares.size(), 0); // Reset all squares to uncovered
//}
