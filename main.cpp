#include "Tournament.h"
#include "InputValidator.h" // Include the new utility class for validation

using namespace std;

int main()
{
    Tournament tour;
    // Enable manual dice mode based on user input
    if (InputValidator::getYesNo("Enable manual dice mode for testing? (y/n): ")) {
        tour.enableManualDiceMode(); // Enable manual mode in the tournament
    }

    tour.start();

    return 0;
}
