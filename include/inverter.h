#ifndef INVERTER_H
#define INVERTER_H

#include <vector>
#include "battery_module.h"

// Declaration to avoid circular dependency
class Storage;

class Inverter {

private:
    /**
     * Batteries managed by the inverter
     */
    std::vector<BatteryModule *> *batteries;

    /**
     * Maximum power that the inverter can charge/discharge in Watts
     */
    float maxPowerToExchange;

    /**
     * Battery current that is flowing to/from inverter in Amps
     */
    float batteryCurrent;

    /**
     * Battery voltage in Volts
     */
    float batteryVoltage;

    /**
     * Power inverter is releasing/storing in the batteries in Watts
     *      - positive value notates inverter power is flowing into the batteries (charging)
     *      - negative value notates battery power is flowing into the inverter (discharging)
     */
    float inverterPower;

    /**
     * Inverter sensed grid frequency in Hertz
     */
    float gridFrequency;

    /**
     * Inverter sensed grid Voltage in Volts
     */
    float gridVoltage;

public:
    // Constructors

    Inverter();

    explicit Inverter(float maxPower);

    Inverter(float maxPower, std::vector<BatteryModule *> *batteries);

    Inverter(float maxPower, float inverterPower, std::vector<BatteryModule *> *batteries);

    // Methods

    /**
     * @param powerToCharge The amount of energy to be charged
     *
     * @return The amount of energy that was not charged in the inverter.
     *         Could be for a limit in the inverter or in the batteries.
     */
    virtual float charge(float powerToCharge);

    /**
     * @param powerToDischarge The amount of power to discharge. It must be a negative value and can
     *                         be greater than the maximum allowed for the inverter or the batteries.
     *                         Inside the method we will check if the inverter can discharge the power.
     *
     * @return The amount of power that could not be obtained and is missing to fulfill the request.
     *         Ex.:
     *         If the powerToDischarge is -1000W and the inverter can only discharge 700W
     *         (for maximum limit in himself or in the batteries), the function will
     *         return the -300W needed to complete the request
     */
    virtual float discharge(float powerToDischarge);

    // Getters

    float getMaxPowerToExchange() const;

    float getBatteryVoltage() const;

    float getBatteryCurrent() const;

    float getInverterPower() const;

    float getGridFrequency() const;

    float getGridVoltage() const;

    // Setters

    void setMaxPowerToExchange(float power);

    void setBatteryCurrent(float current);

    void setInverterPower(float power);

    void setGridFrequency(float frequency);

    void setGridVoltage(float voltage);

    void setBatteries(std::vector<BatteryModule *> *pBatteries);
};

#endif
