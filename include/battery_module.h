#ifndef BATTERY_MODULE_H
#define BATTERY_MODULE_H

class BatteryModule {

private:
    /**
     * Module temperature in Celsius degrees.
     *
     * On the purpose of this project, the temperature is not used, but
     * will be acquire a random value in the constructor.
     */
    float temperature;

    /**
     * Module voltage in Volts.
     */
    float voltage;

    /*+
     * Maximum power that the battery module can charge or discharge in Watts.
     */
    float maxPower;

public:
    // Constructor

    BatteryModule(float maxPower, float voltage);

    // Methods

    /**
     * Charge the battery module with the given power.
     *
     * Execute the inverse operation of {@link discharge()}.
     *
     * @param powerToCharge The amount of power to charge the battery module in Watts.
     *
     * @return The amount of power that could not be allocated in the module.
     *         Right now, that happens when the power to charge is greater than the maximum power.
     *
     * @see maxPower
     */
    virtual float charge(float powerToCharge);

    /**
     * Try to discharge the battery module with a quantity of power.
     *
     * Execute the inverse operation of {@link charge()}.
     *
     * @param powerToDischarge The amount of power to discharge the battery module in Watts.
     *
     * @return The amount of power needed to fulfill the initial request indicate in the
     *         parameter when the module can not discharge all the power requested.
     */
    virtual float discharge(float powerToDischarge);

    // Getters

    float getTemperature() const;

    float getVoltage() const;

    float getMaxPower() const;
};

#endif
