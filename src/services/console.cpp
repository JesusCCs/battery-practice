#include <iomanip>
#include <sstream>
#include "../../include/console.h"

void Console::print(const std::string &message) {
    std::cout << message << std::endl;
}

void Console::printSeparator() {
    std::cout << "----------------------------------------" << std::endl;
}

std::string Console::fixNumber(float value, int precision) {
    std::stringstream stream;

    stream << std::fixed << std::setprecision(precision) << value;

    return stream.str();
}

void Console::printTitle(const std::string &message) {
    auto len = message.length();

    std::cout << std::endl;

    std::cout << "+" << std::string(len + 2, '-') << "+" << std::endl;

    std::cout << "| " << message << " |" << std::endl;

    std::cout << "+" << std::string(len + 2, '-') << "+" << std::endl;

    std::cout << std::endl;
}

float Console::askForFloat(const std::string &message, bool positiveOnly) {
    float value;
    std::string input;

    std::cout << message << std::endl;

    while (true) {
        std::getline(std::cin, input);

        try {
            value = std::stof(input);

            if (positiveOnly && value < 0) {
                std::cout << "Value cannot be negative, please try again." << std::endl;
            } else {
                break;
            }
        } catch (...) {
            std::cout << "Invalid value, please try again." << std::endl;
        }
    }

    return value;
}

int Console::askForInteger(const std::string& message, int max, int min)
{
    float value;

    while (true) {
        value = Console::askForFloat(message, min >= 0);

        if (value > max) {
            std::cout << "Value cannot be greater than " << max << ", please try again." << std::endl;
            continue;
        }

        if (value < min) {
            std::cout << "Value cannot be less than " << min << ", please try again." << std::endl;
            continue;
        }

        if (value != (int)value) {
            std::cout << "Value must be an integer, please try again." << std::endl;
            continue;
        }

        break;
    }

    return (int)value;
}

int Console::askForChoice(const std::string &message, std::vector<std::string> options) {
    int choice;

    std::cout << message << std::endl;

    for (int i = 1; i <= options.size(); i++) {
        std::cout << "  " << i << ". " << options[i - 1] << std::endl;
    }

    choice = Console::askForInteger("Please enter your choice:", options.size(), 1);

    return choice;
}

void Console::printTable(std::vector<std::vector<std::string>> data) {
    std::vector<int> maxColumnWidths(data[0].size(), 0);

    for (auto row: data) {
        for (int i = 0; i < row.size(); i++) {
            maxColumnWidths[i] = std::max(maxColumnWidths[i], (int) row[i].size());
        }
    }

    bool firstRow = true;

    for (auto row: data) {
        for (int i = 0; i < row.size(); i++) {
            int space = maxColumnWidths[i] - row[i].size();

            int leftSpace = space / 2;

            int rightSpace = space - leftSpace;

            std::cout << std::string(leftSpace, ' ') << row[i] << std::string(rightSpace, ' ') << " ";
        }

        std::cout << std::endl;

        // If this is the first row, we print a line to separate the header from the data.
        if (firstRow) {
            for (int maxColumnWidth: maxColumnWidths) {
                std::cout << std::string(maxColumnWidth, '-') << " ";
            }

            std::cout << std::endl;

            firstRow = false;
        }
    }
}
