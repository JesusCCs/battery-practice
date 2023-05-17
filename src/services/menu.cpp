#include "../../include/menu.h"

int BASIC_SETUP_MAX_BATTERIES = 2;
int STANDARD_SETUP_MAX_BATTERIES = 3;
int PRO_SETUP_MAX_BATTERIES = 5;

Menu::Menu() {
    this->console = new Console(&std::cin);
}

void Menu::showIntro() {
    auto option = console->askForChoice("You can choose between the following options:", {
            "Create with only the parameters to use in the algorithm (power)",
            "Create with all the parameters",
    });

    onlyImportantParameters = option == 1;

    auto setup = console->askForChoice("Now, you must choose the system setup:", {
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

    maxBatteries = console->askForInteger(
            "Enter the maximum number of batteries:", possibleMaxBattery, 1
    );

    console->printSeparator();
}


PhotovoltaicPanel *Menu::createPhotovoltaicPanel() const {
    console->printTitle("Photovoltaic Panel Data");

    auto voltageProduction = onlyImportantParameters ? 200.0f : console->askForFloat(
            "Enter the photovoltaic panel voltage production:", true
    );

    auto powerProduction = console->askForFloat(
            "Enter the photovoltaic panel power production:", true
    );

    auto photovoltaicPanel = new PhotovoltaicPanel(powerProduction, voltageProduction);

    return photovoltaicPanel;
}

House *Menu::createHouse() const {
    console->printTitle("House Data");

    auto houseVoltage = onlyImportantParameters ? 230.0f : console->askForFloat(
            "Enter the house voltage:", true
    );

    auto houseFrequency = onlyImportantParameters ? 50.0f : console->askForFloat(
            "Enter the house frequency:", true
    );

    auto house = new House(houseVoltage, houseFrequency);

    auto powerConsumption = console->askForFloat("Enter the house power consumption:", true);

    house->setPowerConsumption(powerConsumption);

    return house;
}

Grid *Menu::createGrid() const {
    if (!onlyImportantParameters) {
        console->printTitle("Grid Data");
    }

    auto gridVoltage = onlyImportantParameters ? 240.0f : console->askForFloat(
            "Enter the grid voltage:", true
    );

    auto gridFrequency = onlyImportantParameters ? 50.0f : console->askForFloat(
            "Enter the grid frequency:", true
    );

    return new Grid(gridVoltage, gridFrequency);
}

Storage *Menu::createStorage() const {
    console->printTitle("Storage Data");

    auto maxPowerInverter = console->askForFloat(
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
        float maxPower = console->askForFloat(
            "Enter the max power of the battery #" + std::to_string(i + 1) + ":", true
        );

        float voltage = onlyImportantParameters ? 12 : console->askForFloat(
            "Enter the voltage of the battery #" + std::to_string(i + 1) + ":", true
        );

        batteries->push_back(new BatteryModule(maxPower, voltage));
    }

    return batteries;
}

void Menu::showResults(House *house, PhotovoltaicPanel *panel, Grid *grid, Storage *storage) const {
    console->printTitle("Results");

    // BMS Info

    console->print("A table with the selected data for the battery modules:\n");

    auto batteries = storage->getBatteryModules();

    auto batteriesInfo = std::vector<std::vector<std::string>>();

    auto batteryTotal = 0.0f;

    batteriesInfo.push_back({"Battery", "Maximum power"});

    for (int i = 0; i < batteries->size(); i++) {
        batteriesInfo.push_back({
            std::to_string(i + 1),
            console->fixNumber(batteries->at(i)->getMaxPower(), 2) + " W"
        });

        batteryTotal += batteries->at(i)->getMaxPower();
    }

    batteriesInfo.push_back({
        "Total:",
        console->fixNumber(batteryTotal, 2) + " W"
    });

    console->printTable(batteriesInfo);

    // Final Results Info

    console->print("\nA table with the final status for the elements:\n");

    console->printTable({
        {"House Power Consumption", "PV Production", "Grid Exchange", "Storage Exchange"},
        {
            console->fixNumber(house->getPowerConsumption(), 2) + " W",
            console->fixNumber(panel->getPowerProduction(), 2) + " W",
            console->fixNumber(grid->getPowerExchange(), 2) + " W",
            console->fixNumber(storage->getPowerExchange(), 2) + " W"
        }
    });
}

