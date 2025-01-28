#pragma once
#ifndef DICE_H
#define DICE_H

#include <utility>
#include <vector>

using namespace std;

class Dice
{
public:
    Dice();
    ~Dice();

    // Roll one die and return the result
    int rollOne() const;

    // Roll two dice and return the pair of results
    pair<int, int> rollTwo() const;

    // Enable manual mode for dice input
    void enableManualMode();  // Declaration here
    // Disable manual mode for dice input
    void disableManualMode(); // Declaration here

    // Roll the dice (manual or random depending on mode)
    pair<int, int> roll() const;
    
    pair<int, int> roll(int diceCount) const; // Overload to accept 1 or 2 dice


private:
    bool manualMode; // True if manual mode is enabled
    mutable vector<int> manualRolls; // Holds the manually entered rolls
    pair<int, int> rollCustom(int diceCount) const;

};

#endif
