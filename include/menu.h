#ifndef MENU_H
#define MENU_H

#include "../include/photovoltaic_panel.h"
#include "../include/house.h"
#include "../include/grid.h"
#include "../include/storage.h"

class Menu {
private:

    bool onlyImportantParameters = false;

    int maxBatteries = 1;

public:

    PhotovoltaicPanel *createPhotovoltaicPanel() const;

    House *createHouse() const;

    Grid *createGrid() const;

    Storage *createStorage() const;

    std::vector<BatteryModule *> *createBatteries() const;

    void showResults(House *house, PhotovoltaicPanel *panel, Grid *grid, Storage *storage) const;

    void showIntro();
};



#endif
