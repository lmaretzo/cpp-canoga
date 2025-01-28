#include "Dice.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

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

Dice::~Dice()
{
    // Nothing special to clean up
}

void Dice::enableManualMode()
{
    manualMode = true;
    cout << "Manual dice mode enabled.\n";
}

void Dice::disableManualMode()
{
    manualMode = false;
    cout << "Manual dice mode disabled.\n";
}

pair<int, int> Dice::roll() const
{
    // Default to rolling two dice
    return rollCustom(2);
}

// New rollCustom method for flexible dice rolling
pair<int, int> Dice::rollCustom(int diceCount) const
{
    if (manualMode)
    {
        cout << "Enter " << diceCount << " dice value(s) (1-6): ";

        int d1 = 0, d2 = 0;
        // Input validation for the first die
        while (!(cin >> d1) || d1 < 1 || d1 > 6)
        {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input for die 1. Enter a value between 1 and 6: ";
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


int Dice::rollOne() const
{
    return (rand() % 6) + 1;
}

pair<int, int> Dice::rollTwo() const
{
    return { rollOne(), rollOne() };
}

pair<int, int> Dice::roll(int diceCount) const
{
    // Reuse the rollCustom method for manual or random rolls
    return rollCustom(diceCount);
}
