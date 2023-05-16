#include <stdexcept>
#include "../../include/battery_module.h"

BatteryModule::BatteryModule(float maxPower, float voltage) {
    if (maxPower <= 0) {
        throw std::invalid_argument("Max power cannot be negative or zero in the battery module");
    }

    this->maxPower = maxPower;

    this->voltage = voltage;

    // The temperature is a random positive value until 60
    this->temperature = (float)(rand() % 60);
}

float BatteryModule::charge(float powerToCharge) {
    if (powerToCharge < 0) {
        throw std::invalid_argument("Power to charge cannot be negative in the battery module");
    }

    auto powerNotAllocated = powerToCharge > maxPower ? powerToCharge - maxPower : 0;

    return powerNotAllocated;
}

float BatteryModule::discharge(float powerToDischarge) {
    if (powerToDischarge > 0) {
        throw std::invalid_argument("Power to discharge cannot be positive in the battery module");
    }

    // The power to discharge is negative, so we obtain the max power to discharge as a negative value too
    auto maxPowerToDischarge = maxPower * -1;

    auto powerMissing = powerToDischarge < maxPowerToDischarge ? powerToDischarge - maxPowerToDischarge : 0;

    return powerMissing;
}


float BatteryModule::getTemperature() const {
    return temperature;
}

float BatteryModule::getVoltage() const {
    return voltage;
}

float BatteryModule::getMaxPower() const {
    return maxPower;
}
