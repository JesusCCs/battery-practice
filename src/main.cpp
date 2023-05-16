#include <iostream>
#include "../include/photovoltaic_panel.h"
#include "../include/house.h"
#include "../include/grid.h"
#include "../include/storage.h"
#include "../include/console.h"

PhotovoltaicPanel *createPhotovoltaicPanel();

House *createHouse();

Grid *createGrid();

Storage *createStorage();

std::vector<BatteryModule *> *createBatteries();

void showResults(House *house, PhotovoltaicPanel *panel, Grid *grid, Storage *storage);

int main() {
    auto photovoltaicPanel = createPhotovoltaicPanel();

    auto house = createHouse();

    auto grid = createGrid();

    auto storage = createStorage();

    storage->manageEnergyOf(house, photovoltaicPanel, grid);

    showResults(house, photovoltaicPanel, grid, storage);

    return 0;
}


PhotovoltaicPanel *createPhotovoltaicPanel() {
    Console::printTitle("Photovoltaic Panel Data");

    auto defaultVoltage = 200.0f;

    auto powerProduction = Console::askForFloat("Enter the photovoltaic panel power production:", true);

    auto photovoltaicPanel = new PhotovoltaicPanel(powerProduction, defaultVoltage);

    return photovoltaicPanel;
}

House *createHouse() {
    Console::printTitle("House Data");

    auto defaultVoltage = 230.0f;
    auto defaultFrequency = 50.0f;

    auto house = new House(defaultVoltage, defaultFrequency);

    auto powerConsumption = Console::askForFloat("Enter the house power consumption:", true);

    house->setPowerConsumption(powerConsumption);

    return house;
}

Grid *createGrid() {
    auto defaultVoltage = 240.0f;
    auto defaultFrequency = 50.0f;

    return new Grid(defaultVoltage, defaultFrequency);
}

Storage *createStorage() {
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

std::vector<BatteryModule *> *createBatteries()
{
    auto batteries = new std::vector<BatteryModule *>();

    batteries->push_back(new BatteryModule(100.0f, 12));
    batteries->push_back(new BatteryModule(200.0f, 12));
    batteries->push_back(new BatteryModule(300.0f, 12));

    return batteries;
}

void showResults(House *house, PhotovoltaicPanel *panel, Grid *grid, Storage *storage) {
    Console::printTitle("Results");

    // BMS Info

    Console::print("Battery Modules:\n");

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

    Console::print("\nFinal Results:\n");

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