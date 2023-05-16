#ifndef STORAGE_H
#define STORAGE_H

#include "inverter.h"
#include "battery_module.h"
#include "em_controller.h"
#include <vector>

class Storage {
private:
    /**
     * Reference to the inverter object that will be used to control the energy flow.
     */
    Inverter *inverter;

    /**
     * Reference to the EMController object that will be used to execute the energy management algorithm.
     */
    EMController *controller;

    /**
     * Reference to the batteries modules that will be used to store the energy.
     */
    std::vector<BatteryModule *> *batteries;

public:
    // Constructors

    Storage();

    Storage(Inverter *inverter, EMController *controller, std::vector<BatteryModule *> *batteries);

    // Methods

    /**
     * The function will receive the house, photovoltaic panel and
     * grid objects to control the energy flow between them.
     */
    void manageEnergyOf(House *house, PhotovoltaicPanel *photovoltaicPanel, Grid *grid);

    /**
     * @param powerToCharge The amount of energy to be charged
     *
     * @return The amount of energy that was not charged in the storage.
     *         Could be for a limit in the inverter or in the batteries modules.
     */
    virtual float charge(float powerToCharge);

    /**
     * @param powerToDischarge The total amount of power needed to complete the request. It must be a negative value.
     *
     * @return The amount of power that could not be obtained and is missing to fulfill the request.
     *         Ex.:
     *         If the powerToDischarge is -1000W and the inverter can only
     *         discharge 700W (for maximum limit or not enough storage), the
     *         function will return the -300W needed to complete the request
     */
    virtual float discharge(float powerToDischarge);

    // Getters

    Inverter *getInverter() const;

    std::vector<BatteryModule *> *getBatteryModules() const;

    float getPowerExchange() const;

    // Setters

    void setInverter(Inverter *inverter);
};

#endif
