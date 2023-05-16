#ifndef GRID_H
#define GRID_H

class Grid {

private:
    /**
     * Amount of power that is sold and bought to/from the utility provider.
     */
    float powerExchange;

    /**
     * Grid voltage in Volts
     */
    float voltageGrid;

    /**
     * Grid frequency in Hertz
     */
    float frequencyGrid;

public:
    // Constructors

    Grid();

    Grid(float voltageGrid, float frequencyGrid);

    // Methods

    /**
     * This is not a setter. It will sum the power given to the powerExchange state variable.
     *
     * @param power Positive will indicate
     */
    virtual void updatePowerExchange(float power);

    // Getters

    float getPowerExchange() const;

    float getVoltage() const;

    float getFrequency() const;
};

#endif
