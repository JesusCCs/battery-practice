#include "../../include/grid.h"

Grid::Grid() = default;

Grid::Grid(float voltageGrid, float frequencyGrid) {
    this->voltageGrid = voltageGrid;
    this->frequencyGrid = frequencyGrid;

    this->powerExchange = 0;
}

void Grid::updatePowerExchange(float power) {
    powerExchange += power;
}

float Grid::getPowerExchange() const {
    return powerExchange;
}

float Grid::getVoltage() const {
    return voltageGrid;
}

float Grid::getFrequency() const {
    return frequencyGrid;
}
