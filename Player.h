/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

using namespace std;

/* *********************************************************************
Class Name: Player
Purpose: Represents a player in the Canoga game, managing their board and actions.
Attributes:
    - playerName: The name of the player.
    - computer: Boolean indicating if the player is AI-controlled.
    - score: The player's current score.
    - squares: A vector representing the covered/uncovered squares.
Functions:
    - Player(): Default constructor.
    - Player(string name, bool isComputer, int boardSize): Initializes a player with given attributes.
    - ~Player(): Destructor.
    - getName(): Returns the player's name.
    - isComputerPlayer(): Returns true if the player is AI-controlled.
    - getScore(): Returns the player's score.
    - setName(string name): Sets the player's name.
    - setIsComputer(bool flag): Sets the player type (human or AI).
    - addToScore(int points): Adds points to the player's score.
    - coverSquare(int squareLabel): Covers a square.
    - uncoverSquare(int squareLabel): Uncovers a square.
    - areAllCovered(): Checks if all squares are covered.
    - areAllUncovered(): Checks if all squares are uncovered.
    - getSquares(): Returns the player's squares.
    - printBoard(): Prints the player's board.
    - offerHint(): Placeholder for future strategy logic.
Reference: None
********************************************************************* */

// New structure that holds a move decision.
struct MoveDecision {
    bool cover;             // true if the move is to cover; false if to uncover
    vector<int> squares;    // the chosen squares (empty if skipping)
};

class Player
{
public:
    Player();
    Player(const string& name, int boardSize);
    ~Player();

    // Getters
    string getName() const;
   // bool isComputerPlayer() const;
    int getScore() const;

    // Setters
    void setName(const string& name);
   // void setIsComputer(bool flag);

    // Score methods
    void addToScore(int points);

    // Board squares
    // For simplicity, fixing the board to 9 squares for now.
    // squares[i] == 0 => uncovered, squares[i] == (i+1) => covered
    bool coverSquare(int squareLabel);   // label: 1..9
    bool uncoverSquare(int squareLabel); // label: 1..9

    bool areAllCovered() const;   // check if all squares are covered
    bool areAllUncovered() const; // check if all squares are uncovered

    // return a copy of the squares array 
    vector<int> getSquares() const;

    void printBoard() const; // Print the player's current board

    // New unified virtual method for decision making.
    virtual MoveDecision decideMove(int diceSum);



    // Placeholder for future "hint" or "strategy" method
    void offerHint();

    void resetSquares(int boardSize); // Pass the board size to resetSquares




private:
    string playerName;
    //bool computer;
    int score;


    vector<int> squares;  // size=9 in this simplified version
};

#endif
