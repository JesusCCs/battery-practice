#include "../../include/menu.h"
#include "../../include/console.h"

int BASIC_SETUP_MAX_BATTERIES = 2;
int STANDARD_SETUP_MAX_BATTERIES = 3;
int PRO_SETUP_MAX_BATTERIES = 5;

void Menu::showIntro() {
    auto option = Console::askForChoice("You can choose between the following options:", {
            "Create with only the parameters to use in the algorithm (power)",
            "Create with all the parameters",
    });

    onlyImportantParameters = option == 1;

    auto setup = Console::askForChoice("Now, you must choose the system setup:", {
            "Basic, up to two battery modules",
            "Standard, up to three battery modules",
            "Pro, up to five battery modules",
    });

    int possibleMaxBattery;

    switch (setup) {
        case 1:
            possibleMaxBattery = BASIC_SETUP_MAX_BATTERIES;
            break;
        case 2:
            possibleMaxBattery = STANDARD_SETUP_MAX_BATTERIES;
            break;
        case 3:
            possibleMaxBattery = PRO_SETUP_MAX_BATTERIES;
            break;

        default:
            throw std::invalid_argument("Invalid setup");
    }

    maxBatteries = Console::askForInteger(
            "Enter the maximum number of batteries:", possibleMaxBattery, 1
    );

    Console::printSeparator();
}


PhotovoltaicPanel *Menu::createPhotovoltaicPanel() const {
    Console::printTitle("Photovoltaic Panel Data");

    auto voltageProduction = onlyImportantParameters ? 200.0f : Console::askForFloat(
            "Enter the photovoltaic panel voltage production:", true
    );

    auto powerProduction = Console::askForFloat(
            "Enter the photovoltaic panel power production:", true
    );

    auto photovoltaicPanel = new PhotovoltaicPanel(powerProduction, voltageProduction);

    return photovoltaicPanel;
}

House *Menu::createHouse() const {
    Console::printTitle("House Data");

    auto houseVoltage = onlyImportantParameters ? 230.0f : Console::askForFloat(
            "Enter the house voltage:", true
    );

    auto houseFrequency = onlyImportantParameters ? 50.0f : Console::askForFloat(
            "Enter the house frequency:", true
    );

    auto house = new House(houseVoltage, houseFrequency);

    auto powerConsumption = Console::askForFloat("Enter the house power consumption:", true);

    house->setPowerConsumption(powerConsumption);

    return house;
}

Grid *Menu::createGrid() const {
    if (!onlyImportantParameters) {
        Console::printTitle("Grid Data");
    }

    auto gridVoltage = onlyImportantParameters ? 240.0f : Console::askForFloat(
            "Enter the grid voltage:", true
    );

    auto gridFrequency = onlyImportantParameters ? 50.0f : Console::askForFloat(
            "Enter the grid frequency:", true
    );

    return new Grid(gridVoltage, gridFrequency);
}

Storage *Menu::createStorage() const {
    Console::printTitle("Storage Data");

    auto maxPowerInverter = Console::askForFloat(
            "Enter the max power that the inverter can charge/discharge:", true
    );

    auto inverter = new Inverter(maxPowerInverter);

    auto controller = new EMController();

    auto batteries = createBatteries();

    auto storage = new Storage(inverter, controller, batteries);

    return storage;
}

std::vector<BatteryModule *> *Menu::createBatteries() const {
    auto batteries = new std::vector<BatteryModule *>();

    for (int i = 0; i < maxBatteries; i++) {
        float maxPower = Console::askForFloat(
            "Enter the max power of the battery #" + std::to_string(i + 1) + ":", true
        );

        float voltage = onlyImportantParameters ? 12 : Console::askForFloat(
            "Enter the voltage of the battery #" + std::to_string(i + 1) + ":", true
        );

        batteries->push_back(new BatteryModule(maxPower, voltage));
    }

    return batteries;
}

void Menu::showResults(House *house, PhotovoltaicPanel *panel, Grid *grid, Storage *storage) const {
    Console::printTitle("Results");

    // BMS Info

    Console::print("A table with the selected data for the battery modules:\n");

    auto batteries = storage->getBatteryModules();

    auto batteriesInfo = std::vector<std::vector<std::string>>();

    auto batteryTotal = 0.0f;

    batteriesInfo.push_back({"Battery", "Maximum power"});

    for (int i = 0; i < batteries->size(); i++) {
        batteriesInfo.push_back({
            std::to_string(i + 1),
            Console::fixNumber(batteries->at(i)->getMaxPower(), 2) + " W"
        });

        batteryTotal += batteries->at(i)->getMaxPower();
    }

    batteriesInfo.push_back({
        "Total:",
        Console::fixNumber(batteryTotal, 2) + " W"
    });

    Console::printTable(batteriesInfo);

    // Final Results Info

    Console::print("\nA table with the final status for the elements:\n");

    Console::printTable({
        {"House Power Consumption", "PV Production", "Grid Exchange", "Storage Exchange"},
        {
            Console::fixNumber(house->getPowerConsumption(), 2) + " W",
            Console::fixNumber(panel->getPowerProduction(), 2) + " W",
            Console::fixNumber(grid->getPowerExchange(), 2) + " W",
            Console::fixNumber(storage->getPowerExchange(), 2) + " W"
        }
    });
}

