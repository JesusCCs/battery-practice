#ifndef HOUSE_H
#define HOUSE_H

class House {
private:
    /**
     * Voltage of the house grid
     */
    float voltageGrid;

    /**
     * Frequency of the house grid
     */
    float frequencyGrid;

    /**
     * Amount of power that is going into the house in Watts
     */
    float powerInto;

    /**
     * Electric current flowing into the house in Amps
     */
    float currentInto;

public:
    // Constructors

    House();

    House(float voltageGrid, float frequencyGrid);

    // Getters

    float getVoltageGrid() const;

    float getFrequencyGrid() const;

    float getPowerInto() const;

    float getCurrentInto() const;

    /**
     * An alias for getPowerInto(), to obtain a more declarative name.
     *
     * @see powerInto
     */
    virtual float getPowerConsumption();

    // Setters

    void setVoltageGrid(float voltage);

    void setFrequencyGrid(float frequency);

    void setPowerInto(float power);

    void setCurrentInto(float current);

    /**
     * An alias for setPowerInto(), to obtain a more declarative name.
     *
     * @see powerInto
     */
    void setPowerConsumption(float power);
};

#endif
