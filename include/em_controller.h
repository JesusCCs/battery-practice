#ifndef EM_CONTROLLER_H
#define EM_CONTROLLER_H

#include "grid.h"
#include "house.h"
#include "photovoltaic_panel.h"

// Declaration to avoid circular dependency
class Storage;

class EMController {

private:
    /**
     * The Storage that the EMController belongs to.
     *
     * Although the Storage is a require state in this class to function properly, the set of
     * the Storage has been delegate to the constructor of the Storage itself, not to this class.
     *
     * The reason is that the Storage needs a reference to the controller, so we have a circular need between
     * both classes. My solution has been to allow the creation of the EMController without parameters, and
     * then, the moment that the Storage is created (and require a EMController for that), is the moment
     * where we set the Storage in the EMController.
     */
    Storage *storage;

public:
    // Constructor

    EMController();

    // Methods

    /**
     * This method receives the current state of the house, photovoltaic panel, and grid, and determines the actions needed.
     *
     * It implements the core logic of the exercise as described in the assignment:
     *
     * 1. When PV production exceeds house consumption, the following order of operations is observed:
     *     a. The storage system is charged with the surplus power.
     *     b. Any remaining power is directed to the grid.
     *
     * 2. When house consumption exceeds PV production:
     *     a. The storage system supplies power to the house.
     *     b. If further power is required, it is provided by the grid.
     */
    void handle(House *house, PhotovoltaicPanel *photovoltaicPanel, Grid *grid);

    // Setters

    /**
     * We need the setter os this property because the EMController needs to know the Storage that it belongs to.
     */
    void setStorage(Storage *pStorage);
};

#endif
