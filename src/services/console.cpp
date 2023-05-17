#include <iomanip>
#include <sstream>
#include "../../include/console.h"

Console::Console(std::istream *reader) {
    this->reader = reader;
}

void Console::print(const std::string &message) const {
    std::cout << message << std::endl;
}

void Console::printSeparator() const {
    std::cout << "----------------------------------------" << std::endl;
}

void Console::printTitle(const std::string &message) const {
    auto len = message.length();

    std::cout << std::endl;

    std::cout << "+" << std::string(len + 2, '-') << "+" << std::endl;

    std::cout << "| " << message << " |" << std::endl;

    std::cout << "+" << std::string(len + 2, '-') << "+" << std::endl;

    std::cout << std::endl;
}

void Console::printTable(std::vector<std::vector<std::string>> data) const {
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

std::string Console::fixNumber(float value, int precision) const {
    std::stringstream stream;

    stream << std::fixed << std::setprecision(precision) << value;

    return stream.str();
}

float Console::askForFloat(const std::string &message, bool positiveOnly) const {
    float value;
    std::string input;

    print(message);

    while (true) {
        std::getline(*reader, input);

        try {
            value = std::stof(input);

            if (positiveOnly && value < 0) {
                print("Value cannot be negative, please try again.");
            } else {
                break;
            }
        } catch (...) {
            print("Invalid value, please try again.");
        }
    }

    return value;
}

int Console::askForInteger(const std::string &message, int max, int min) const {
    float value;

    while (true) {
        value = this->askForFloat(message, min >= 0);

        if (value > max) {
            std::cout << "Value cannot be greater than " << max << ", please try again." << std::endl;
            continue;
        }

        if (value < min) {
            std::cout << "Value cannot be less than " << min << ", please try again." << std::endl;
            continue;
        }

        if (value != (int) value) {
            print("Value must be an integer, please try again.");
            continue;
        }

        break;
    }

    return (int) value;
}

int Console::askForChoice(const std::string &message, std::vector<std::string> options) const {
    int choice;

    print(message);

    for (int i = 1; i <= options.size(); i++) {
        std::cout << "  " << i << ". " << options[i - 1] << std::endl;
    }

    choice = this->askForInteger("Please enter your choice:", options.size(), 1);

    return choice;
}

