#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <iostream>
#include <limits>
#include <cctype>

class InputValidator {
public:
    // Prompts for a yes/no input and validates it
    static bool getYesNo(const std::string& prompt);
};

#endif
