/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/


#include "Dice.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>        // for std::string, std::getline
#include <sstream>       // for std::stringstream

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
Purpose: Handles both manual and random dice rolling, based on mode.
         Allows typing a single '0' to skip, even if two dice are expected.
Parameters:
    - diceCount: how many dice (1 or 2).
Return Value: (d1, d2) for valid inputs; or (0,0) if user skips.
Algorithm:
    1) If !manualMode, return random rolls.
    2) Otherwise:
       a) Enter a loop that prompts the user.
       b) Read an entire line with std::getline.
       c) If the line is empty, tell them to retry (no "invalid" message).
       d) Tokenize into integers:
          - If exactly one token == 0, skip.
          - Else if exactly diceCount tokens: check each is in [1..6].
            If valid, return it; if any 0 or out of range => skip or error.
          - Otherwise, "Invalid number of inputs" => re-prompt.
Reference: None
********************************************************************* */
pair<int, int> Dice::rollCustom(int diceCount) const
{
    if (!manualMode)
    {
        // Normal random rolling
        return (diceCount == 1) ? make_pair(rollOne(), 0) : rollTwo();
    }

    while (true)
    {
        cout << "Enter " << diceCount
            << " dice value(s) (1-6): ";

        // Read a full line
        string line;
        if (!getline(cin, line)) // if the stream fails, clear & continue
        {
            cin.clear();
            continue;
        }

        // If the user typed absolutely nothing
        if (line.empty())
        {
            cout << "No input. Please enter numbers 1..6\n";
            continue;
        }

        // Parse the line into integers
        stringstream ss(line);
        vector<int> tokens;
        int val;
        while (ss >> val)
        {
            tokens.push_back(val);
        }

        //// 1) If user typed exactly one token == 0, skip
        //if (tokens.size() == 1 && tokens[0] == 0)
        //{
        //    cout << "Skipping roll.\n";
        //    return { 0, 0 };
        //}

        // 2) If user typed exactly diceCount tokens, validate them
        if (tokens.size() == static_cast<size_t>(diceCount))
        {
            bool allValid = true;
            // Check each token is in [1..6]
            for (int d : tokens)
            {
                if (d < 1 || d > 6)
                {
                    allValid = false;
                    break;
                }
            }

            if (allValid)
            {
                // Return them properly
                if (diceCount == 1)
                {
                    return { tokens[0], 0 };
                }
                else
                {
                    return { tokens[0], tokens[1] };
                }
            }
            else
            {
                // Maybe they typed "6 0" or "7" or something
                cout << "Invalid dice values; must be in [1..6].\n";
                continue; // re-prompt
            }
        }
        else
        {
            // e.g. typed "3 4 5" for diceCount=2, or typed "3" for diceCount=2
            cout << "Invalid number of inputs. Please enter exactly "
                << diceCount << " \n";
            continue; // re-prompt
        }
    }

    // Should never reach here
    return { 0, 0 };
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
