/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#pragma once
#ifndef DICE_H
#define DICE_H

#include <utility>
#include <vector>

using namespace std;

/* *********************************************************************
Class Name: Dice
Purpose: Handles dice rolling operations, including random and manual input modes.
Attributes:
    - manualMode: A boolean flag to determine whether manual input mode is enabled.
    - manualRolls: A vector storing manually entered dice values for testing purposes.
Functions:
    - Dice(): Constructor that initializes the dice object and seeds the RNG.
    - ~Dice(): Destructor (no special cleanup required).
    - rollOne(): Rolls a single six-sided die and returns the result.
    - rollTwo(): Rolls two six-sided dice and returns their values.
    - enableManualMode(): Activates manual input mode for dice rolls.
    - disableManualMode(): Disables manual mode and reverts to random rolling.
    - roll(): Rolls two dice (default behavior).
    - roll(int diceCount): Rolls either one or two dice, depending on the argument.
    - rollCustom(int diceCount): Handles both manual and random dice rolling.
Reference: None
********************************************************************* */
class Dice
{
public:
    /* *********************************************************************
   Function Name: Dice (Constructor)
   Purpose: Initializes a Dice object and seeds the random number generator.
   Parameters: None
   Return Value: None
   Algorithm:
       1) Initialize manualMode to false.
       2) Ensure the RNG is seeded only once per program execution.
   Reference: None
   ********************************************************************* */
    Dice();

    /* *********************************************************************
    Function Name: ~Dice (Destructor)
    Purpose: Cleans up resources associated with the Dice object.
    Parameters: None
    Return Value: None
    Algorithm: No special cleanup required.
    Reference: None
    ********************************************************************* */
    ~Dice();

    /* *********************************************************************
   Function Name: rollOne
   Purpose: Rolls a single six-sided die.
   Parameters: None
   Return Value: An integer between 1 and 6.
   Algorithm:
       1) Generate a random number between 1 and 6.
       2) Return the result.
   Reference: None
   ********************************************************************* */
    int rollOne() const;

    /* *********************************************************************
    Function Name: rollTwo
    Purpose: Rolls two six-sided dice and returns their values.
    Parameters: None
    Return Value: A pair of integers representing two dice rolls.
    Algorithm:
    1) Call rollOne() twice.
    2) Store the results in a pair and return them.
    Reference: None
    ********************************************************************* */
    pair<int, int> rollTwo() const;

    /* *********************************************************************
    Function Name: enableManualMode
    Purpose: Enables manual mode, allowing users to input custom dice values.
    Parameters: None
    Return Value: None
    Algorithm:
        1) Set manualMode to true.
        2) Notify the user that manual mode has been enabled.
    Reference: None
    ********************************************************************* */
    void enableManualMode();  // Declaration here


    /* *********************************************************************
    Function Name: disableManualMode
    Purpose: Disables manual mode, reverting to random dice rolling.
    Parameters: None
    Return Value: None
    Algorithm:
        1) Set manualMode to false.
        2) Notify the user that manual mode has been disabled.
    Reference: None
    ********************************************************************* */
    void disableManualMode(); // Declaration here

    /* *********************************************************************
    Function Name: roll
    Purpose: Rolls two dice and returns the results.
    Parameters: None
    Return Value: A pair of integers representing two dice rolls.
    Algorithm:
        1) Calls rollCustom(2) to roll two dice.
    Reference: None
    ********************************************************************* */
    pair<int, int> roll() const;
    
    /* *********************************************************************
    Function Name: roll (overloaded)
    Purpose: Rolls either one or two dice based on user input.
    Parameters:
    - diceCount: An integer specifying the number of dice to roll.
    Return Value: A pair of integers representing dice rolls.
    Algorithm:
    1) Calls rollCustom(diceCount) to perform the roll.
    Reference: None
    ********************************************************************* */
    pair<int, int> roll(int diceCount) const; // Overload to accept 1 or 2 dice


private:
    bool manualMode; // True if manual mode is enabled
    mutable vector<int> manualRolls; // Holds the manually entered rolls

    /* *********************************************************************
Function Name: rollCustom
Purpose: Handles both manual and random dice rolling, based on mode.
Parameters:
    - diceCount: An integer specifying how many dice to roll.
Return Value: A pair of integers representing dice values.
Algorithm:
    1) If manualMode is active, prompt user for dice values.
    2) Validate input to ensure numbers are between 1 and 6 (or 0 to skip).
    3) If manualMode is off, generate random dice rolls.
Reference: AI assistance was used to refine the input validation logic.
********************************************************************* */

    pair<int, int> rollCustom(int diceCount) const;

};

#endif
