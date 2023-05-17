#include <stdexcept>
#include <algorithm>
#include "../../include/inverter.h"

Inverter::Inverter() = default;

Inverter::Inverter(float maxPower) {
    this->setMaxPowerToExchange(maxPower);

    this->inverterPower = 0;
}

Inverter::Inverter(float maxPower, std::vector<BatteryModule *> *batteries)
        : Inverter(maxPower) {
    this->batteries = batteries;
}

Inverter::Inverter(float maxPower, float inverterPower, std::vector<BatteryModule *> *batteries)
        : Inverter(maxPower, batteries) {
    this->inverterPower = inverterPower;
}

float Inverter::charge(float powerToCharge) {
    if (powerToCharge < 0) {
        throw std::invalid_argument("Power to charge cannot be negative.");
    }

    float powerNotAllocated, powerLeftToChargeBatteries;

    inverterPower += powerToCharge;

    if (inverterPower > maxPowerToExchange) {
        powerNotAllocated = inverterPower - maxPowerToExchange;
        inverterPower = maxPowerToExchange;
    } else {
        powerNotAllocated = 0;
    }

    powerLeftToChargeBatteries = inverterPower;

    for (auto battery: *batteries) {
        powerLeftToChargeBatteries = battery->charge(powerLeftToChargeBatteries);

        if (powerLeftToChargeBatteries == 0) {
            break;
        }
    }

    inverterPower -= powerLeftToChargeBatteries;

    return powerNotAllocated + powerLeftToChargeBatteries;
}

float Inverter::discharge(float powerToDischarge) {
    if (powerToDischarge > 0) {
        throw std::invalid_argument("Power to discharge cannot be positive in the inverter.");
    }

    float powerMissing, powerLeftToDischargeBatteries;

    auto maxPowerToDischarge = maxPowerToExchange * -1;

    inverterPower += powerToDischarge;

    if (inverterPower < maxPowerToDischarge) {
        powerMissing = inverterPower - maxPowerToDischarge;
        inverterPower = maxPowerToDischarge;
    } else {
        powerMissing = 0;
    }

    powerLeftToDischargeBatteries = inverterPower;

    for (auto battery: *batteries) {
        powerLeftToDischargeBatteries = battery->discharge(powerLeftToDischargeBatteries);

        if (powerLeftToDischargeBatteries == 0) {
            break;
        }
    }

    inverterPower -= powerLeftToDischargeBatteries;

    return powerMissing + powerLeftToDischargeBatteries;
}

float Inverter::getMaxPowerToExchange() const {
    return maxPowerToExchange;
}

float Inverter::getBatteryVoltage() const {
    return batteryVoltage;
}

float Inverter::getBatteryCurrent() const {
    return batteryCurrent;
}

float Inverter::getInverterPower() const {
    return inverterPower;
}

float Inverter::getGridFrequency() const {
    return gridFrequency;
}

float Inverter::getGridVoltage() const {
    return gridVoltage;
}

void Inverter::setMaxPowerToExchange(float power) {
    if (power <= 0) {
        throw std::invalid_argument("Max power cannot be negative or zero in the inverter.");
    }

    this->maxPowerToExchange = power;
}

void Inverter::setBatteryCurrent(float current) {
    this->batteryCurrent = current;
}

void Inverter::setInverterPower(float power) {
    this->inverterPower = power;
}

void Inverter::setGridFrequency(float frequency) {
    this->gridFrequency = frequency;
}

void Inverter::setGridVoltage(float voltage) {
    this->gridVoltage = voltage;
}

void Inverter::setBatteries(std::vector<BatteryModule *> *pBatteries) {
    this->batteries = pBatteries;
}
