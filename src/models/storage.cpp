#include <stdexcept>
#include "../../include/storage.h"

Storage::Storage() = default;

Storage::Storage(Inverter *inverter, EMController *controller, std::vector<BatteryModule *> *batteries) {
    this->inverter = inverter;
    this->inverter->setBatteries(batteries);

    this->controller = controller;
    this->controller->setStorage(this);

    this->batteries = batteries;
}


void Storage::manageEnergyOf(House *house, PhotovoltaicPanel *photovoltaicPanel, Grid *grid) {
    // Until this method is not called, the storage is not 'connected'

    // When we call this method, we can indicate to the inverter the system grid.
    inverter->setGridFrequency(grid->getFrequency());
    inverter->setGridVoltage(grid->getVoltage());

    controller->handle(house, photovoltaicPanel, grid);
}

float Storage::charge(float powerToCharge) {
    if (powerToCharge < 0) {
        throw std::invalid_argument("Power to charge cannot be negative.");
    }

    auto powerNotAllocated = inverter->charge(powerToCharge);

    return powerNotAllocated;
}

float Storage::discharge(float powerToDischarge) {
    if (powerToDischarge > 0) {
        throw std::invalid_argument("Power to discharge cannot be positive.");
    }

    auto powerMissing = inverter->discharge(powerToDischarge);

    return powerMissing;
}

Inverter *Storage::getInverter() const {
    return inverter;
}

std::vector<BatteryModule *> *Storage::getBatteryModules() const {
    return batteries;
}

void Storage::setInverter(Inverter *pInverter) {
    this->inverter = pInverter;
}

float Storage::getPowerExchange() const {
    return inverter->getInverterPower();
}
