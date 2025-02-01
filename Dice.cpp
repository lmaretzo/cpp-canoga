/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/


#include "Dice.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
/* *********************************************************************
Function Name: Dice (Constructor)
Purpose: Initializes the Dice object and seeds the random number generator.
Parameters: None
Return Value: None
Algorithm:
    1) Check if the random number generator has already been seeded.
    2) If not, seed the generator using the current time.
    3) Set manualMode to false.
Reference: None
********************************************************************* */
Dice::Dice() : manualMode(false)
{
    // Seed the random number generator only once
    static bool seeded = false;
    if (!seeded)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }
}

/* *********************************************************************
Function Name: ~Dice (Destructor)
Purpose: Cleans up any allocated resources related to the Dice object.
Parameters: None
Return Value: None
Algorithm: No specific operations are needed in the destructor.
Reference: None
********************************************************************* */
Dice::~Dice()
{
}

/* *********************************************************************
Function Name: enableManualMode
Purpose: Enables manual dice rolling mode, allowing users to enter dice values manually.
Parameters: None
Return Value: None
Algorithm:
    1) Set the manualMode flag to true.
    2) Print a confirmation message.
Reference: None
********************************************************************* */
void Dice::enableManualMode()
{
    manualMode = true;
    cout << "Manual dice mode enabled.\n";
}

/* *********************************************************************
Function Name: disableManualMode
Purpose: Disables manual dice rolling mode, reverting to random dice rolls.
Parameters: None
Return Value: None
Algorithm:
    1) Set the manualMode flag to false.
    2) Print a confirmation message.
Reference: None
********************************************************************* */
void Dice::disableManualMode()
{
    manualMode = false;
    cout << "Manual dice mode disabled.\n";
}

/* *********************************************************************
Function Name: roll
Purpose: Rolls two dice and returns the result. If manual mode is enabled,
         it prompts the user for input.
Parameters: None
Return Value: A pair of integers representing the values of two dice.
Algorithm:
    1) Calls rollCustom(2) to roll two dice.
Reference: None
********************************************************************* */

pair<int, int> Dice::roll() const
{
    // Default to rolling two dice
    return rollCustom(2);
}

/* *********************************************************************
Function Name: rollCustom
Purpose: Rolls a user-defined number of dice. Supports both manual and random mode.
Parameters:
    diceCount - an integer indicating how many dice to roll.
Return Value: A pair of integers representing the dice values.
Algorithm:
    1) If manualMode is enabled, prompt the user for dice values.
    2) Validate user input to ensure numbers are within 1-6 (or 0 to skip).
    3) If manualMode is disabled, generate random dice rolls.
Reference: The logic for manual input validation was AI-assisted
********************************************************************* */
pair<int, int> Dice::rollCustom(int diceCount) const
{
    if (manualMode)
    {
        cout << "Enter " << diceCount << " dice value(s) (1-6): ";

        int d1 = 0, d2 = 0;
        // Input validation for the first die
        while (!(cin >> d1) || (d1 != 0 && (d1 < 1 || d1 > 6)))
        {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input for die 1. Enter a value between 1 and 6, or 0 to skip: ";
        }
        if (d1 == 0)
        {
            cout << "Skipping roll.\n";
            return { 0, 0 };
        }
        // Input validation for the second die (if rolling two dice)
        if (diceCount == 2)
        {
            while (!(cin >> d2) || d2 < 1 || d2 > 6)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input for die 2. Enter a value between 1 and 6: ";
            }
       }

        return { d1, diceCount == 2 ? d2 : 0 };
    }
    else
    {
        // Random dice rolling
        return (diceCount == 1) ? make_pair(rollOne(), 0) : rollTwo();
    }
}

/* *********************************************************************
Function Name: rollOne
Purpose: Rolls a single six-sided die and returns the result.
Parameters: None
Return Value: An integer between 1 and 6.
Algorithm:
    1) Generate a random number between 1 and 6.
    2) Return the result.
Reference: None
********************************************************************* */
int Dice::rollOne() const
{
    return (rand() % 6) + 1;
}

/* *********************************************************************
Function Name: rollTwo
Purpose: Rolls two six-sided dice and returns their values as a pair.
Parameters: None
Return Value: A pair of integers representing the values of two dice.
Algorithm:
    1) Call rollOne() twice to generate two random numbers.
    2) Return the result as a pair.
Reference: None
********************************************************************* */
pair<int, int> Dice::rollTwo() const
{
    return { rollOne(), rollOne() };
}

/* *********************************************************************
Function Name: roll (overloaded)
Purpose: Rolls either one or two dice, depending on the given parameter.
Parameters:
    diceCount - an integer specifying whether to roll one or two dice.
Return Value: A pair of integers representing the dice values.
Algorithm:
    1) Calls rollCustom(diceCount) to handle either one or two dice rolls.
Reference: None
********************************************************************* */
pair<int, int> Dice::roll(int diceCount) const
{
    // Reuse the rollCustom method for manual or random rolls
    return rollCustom(diceCount);
}
