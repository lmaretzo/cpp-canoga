/************************************************************
 * Name:     Lucas Maretzo
 * Project:  P1 Canoga
 * Class:    CMPS366 Operating Systems
 * Date:     3/10/2025
 ************************************************************/

#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <iostream>
#include <limits>
#include <cctype>

/* *********************************************************************
Function Name: getYesNo
Purpose: Ensures the user enters a valid yes ('y') or no ('n') response.
Parameters:
    - prompt: A string message to display to the user.
Return Value:
    - Boolean: Returns true if 'y' is entered, false if 'n' is entered.
Algorithm:
    1) Display the prompt message.
    2) Read user input.
    3) Normalize input to lowercase.
    4) Validate input (only 'y' or 'n' is accepted).
    5) If invalid, prompt again.
Reference: None
********************************************************************* */
bool getYesNo(const std::string& prompt);

#endif
