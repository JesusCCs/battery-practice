#include "../../include/em_controller.h"
#include "../../include/storage.h"

EMController::EMController() = default;

void EMController::setStorage(Storage *pStorage) {
    this->storage = pStorage;
}

void EMController::handle(House *house, PhotovoltaicPanel *panel, Grid *grid) {
    auto pvProduction = panel->getPowerProduction();

    auto houseConsumption = house->getPowerConsumption();

    auto powerDifference = pvProduction - houseConsumption;

    if (powerDifference == 0) {
        // Limit case, no action required
        return;
    }

    if (powerDifference > 0) {
        auto powerToGrid = storage->charge(powerDifference);

        grid->updatePowerExchange(powerToGrid);

        return;
    }

    auto powerFromGrid = storage->discharge(powerDifference);

    grid->updatePowerExchange(powerFromGrid);
}
