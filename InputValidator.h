/************************************************************
 * Name:  Lucas Maretzo
 * Project:  Canoga
 * Date:  1/31/2025
 ************************************************************/

#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <iostream>
#include <limits>
#include <cctype>

 /* *********************************************************************
 Class Name: InputValidator
 Purpose: Provides utility functions for input validation in the Canoga game.
 Attributes: None (all methods are static)
 Functions:
     - getYesNo(const std::string& prompt): Asks the user a yes/no question
       and ensures valid input.
 Reference: None (Entirely self-implemented)
 ********************************************************************* */
class InputValidator {
public:
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
   Reference: None (Entirely self-implemented)
   ********************************************************************* */
    static bool getYesNo(const std::string& prompt);
};

#endif
