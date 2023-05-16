#include "../../include/house.h"

House::House() = default;

House::House(float voltageGrid, float frequencyGrid) {
    this->voltageGrid = voltageGrid;
    this->frequencyGrid = frequencyGrid;

    this->powerInto = 0;
    this->currentInto = 0;
}

float House::getVoltageGrid() const {
    return voltageGrid;
}

float House::getFrequencyGrid() const {
    return frequencyGrid;
}

float House::getPowerInto() const {
    return powerInto;
}

float House::getCurrentInto() const {
    return currentInto;
}

float House::getPowerConsumption() {
    return powerInto;
}

void House::setVoltageGrid(float voltage) {
    this->voltageGrid = voltage;
}

void House::setFrequencyGrid(float frequency) {
    this->frequencyGrid = frequency;
}

void House::setPowerInto(float power) {
    this->powerInto = power;
}

void House::setCurrentInto(float current) {
    this->currentInto = current;
}

void House::setPowerConsumption(float power) {
    this->powerInto = power;
}