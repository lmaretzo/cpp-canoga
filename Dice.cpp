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
    if (manualMode)
    {
        cout << "Enter dice values (one or two numbers between 1 and 6): ";
        int d1 = 0, d2 = 0;
        cin >> d1;

        // Input validation for manual rolls
        while (d1 < 1 || d1 > 6)
        {
            cout << "Invalid input for die 1. Enter a number between 1 and 6: ";
            cin >> d1;
        }

        // Check if a second die is provided
        if (cin.peek() != '\n')
        {
            cin >> d2;
            while (d2 < 1 || d2 > 6)
            {
                cout << "Invalid input for die 2. Enter a number between 1 and 6: ";
                cin >> d2;
            }
        }

        // Return the roll values
        return { d1, d2 > 0 ? d2 : 0 };
    }
    else
    {
        // Roll two dice randomly
        return rollTwo();
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
