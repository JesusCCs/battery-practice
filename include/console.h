#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <vector>

class Console {

public:
    /**
     * Print a message to the console
     */
    static void print(const std::string& message);

    /**
     * Print a separator line to the console
     */
    static void printSeparator();

    /**
     * Show a title to the console
     */
    static void printTitle(const std::string& message);

    /**
     * Obtain a string representation of a number with a given precision
     */
    static std::string fixNumber(float value, int precision);

    /**
     * Method to ask the user for a float value.
     * It will keep asking until the user enters a valid float value.
     *
     * Optionally, you can force to be a positive value.
     */
    static float askForFloat(const std::string& message, bool positiveOnly = false);

    /**
     * Method to present the user with a number of options and ask for a choice.
     * It will keep asking until the user enters a valid choice.
     */
    static int askForChoice(const std::string& message, std::vector<std::string> options);

    /**
     * Show the user a series of data in a table formatted way
     */
    static void printTable(std::vector<std::vector<std::string>> data);
};

#endif


