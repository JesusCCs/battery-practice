#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <vector>

class Console {

private:

    std::istream *reader;

public:

    explicit Console(std::istream *reader);

    /**
     * Print a message to the console
     */
     void print(const std::string& message) const;

    /**
     * Print a separator line to the console
     */
     void printSeparator() const;

    /**
     * Show a title to the console
     */
     void printTitle(const std::string& message) const;

    /**
     * Obtain a string representation of a number with a given precision
     */
     std::string fixNumber(float value, int precision) const;

    /**
     * Method to ask the user for a float value.
     * It will keep asking until the user enters a valid float value.
     *
     * Optionally, you can force to be a positive value.
     */
     float askForFloat(const std::string& message, bool positiveOnly = false) const;

    /**
     * Method to ask the user for a integer value.
     * It will keep asking until the user enters a valid integer value.
     *
     * It will limit the maximum value that the user can enter.
     * Optionally, you can force to be a positive value.
     */
     int askForInteger(const std::string& message, int max, int min) const;

    /**
     * Method to present the user with a number of options and ask for a choice.
     * It will keep asking until the user enters a valid choice.
     */
     int askForChoice(const std::string& message, std::vector<std::string> options) const;

    /**
     * Show the user a series of data in a table formatted way
     */
     void printTable(std::vector<std::vector<std::string>> data) const;
};

#endif


