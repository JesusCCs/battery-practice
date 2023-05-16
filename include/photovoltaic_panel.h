#ifndef PHOTOVOLTAIC_PANEL_H
#define PHOTOVOLTAIC_PANEL_H

class PhotovoltaicPanel {

private:
    /**
     * Power produced by the PV panel in Watts
     */
    float powerProduction;

    /**
     * Voltage produced by the PV panel in Volts
     */
    float voltageProduction;

    /**
     * Electric current production by the PV panel in Amps
     */
    float currentProduction;

public:
    // Constructors

    PhotovoltaicPanel();

    PhotovoltaicPanel(float powerProduction, float voltageProduction, float currentProduction);

    PhotovoltaicPanel(float powerProduction, float voltageProduction);

    // Getters

    virtual float getPowerProduction();

    float getVoltageProduction() const;

    float getCurrentProduction() const;

    // Setters

    void setPowerProduction(float power);

    void setVoltageProduction(float voltage);

    void setCurrentProduction(float current);
};

#endif
