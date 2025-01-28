#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

using namespace std;

// A basic Player class for Human or Computer.
// Strategy/hints will be added later, so we have a placeholder method for that.

class Player
{
public:
    Player();
    Player(const string& name, bool isComputer, int boardSize);
    ~Player();

    // Getters
    string getName() const;
    bool isComputerPlayer() const;
    int getScore() const;

    // Setters
    void setName(const string& name);
    void setIsComputer(bool flag);

    // Score methods
    void addToScore(int points);

    // Board squares
    // For simplicity, let's fix the board to 9 squares for now.
    // squares[i] == 0 => uncovered, squares[i] == (i+1) => covered
    bool coverSquare(int squareLabel);   // label: 1..9
    bool uncoverSquare(int squareLabel); // label: 1..9

    bool areAllCovered() const;   // check if all squares are covered
    bool areAllUncovered() const; // check if all squares are uncovered

    // Return a copy of the squares array (for display, etc.)
    vector<int> getSquares() const;

    void printBoard() const; // Print the player's current board


    // Placeholder for future "hint" or "strategy" method
    // (We will implement advanced logic later.)
    void offerHint();

    void resetSquares(int boardSize); // Pass the board size to resetSquares




private:
    string playerName;
    bool computer;
    int score;


    vector<int> squares;  // size=9 in this simplified version
};

#endif
