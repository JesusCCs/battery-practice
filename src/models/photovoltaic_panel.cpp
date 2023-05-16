#include "../../include/photovoltaic_panel.h"

PhotovoltaicPanel::PhotovoltaicPanel() = default;

PhotovoltaicPanel::PhotovoltaicPanel(float powerProduction, float voltageProduction, float currentProduction) {
    this->powerProduction = powerProduction;
    this->voltageProduction = voltageProduction;
    this->currentProduction = currentProduction;
}

PhotovoltaicPanel::PhotovoltaicPanel(float powerProduction, float voltageProduction) {
    this->powerProduction = powerProduction;
    this->voltageProduction = voltageProduction;

    this->currentProduction = powerProduction / voltageProduction;
}

float PhotovoltaicPanel::getVoltageProduction() const {
    return this->voltageProduction;
}

float PhotovoltaicPanel::getCurrentProduction() const {
    return this->currentProduction;
}

float PhotovoltaicPanel::getPowerProduction() {
    return this->powerProduction;
}

void PhotovoltaicPanel::setPowerProduction(float power) {
    this->powerProduction = power;
}

void PhotovoltaicPanel::setVoltageProduction(float voltage) {
    this->voltageProduction = voltage;
}

void PhotovoltaicPanel::setCurrentProduction(float current) {
    this->currentProduction = current;
}
