#ifndef MENU_H
#define MENU_H

#include "../include/photovoltaic_panel.h"
#include "../include/house.h"
#include "../include/grid.h"
#include "../include/storage.h"

class Menu {
private:

public:

    PhotovoltaicPanel *createPhotovoltaicPanel();

    House *createHouse();

    Grid *createGrid();

    Storage *createStorage();

    std::vector<BatteryModule *> *createBatteries();

    void showResults(House *house, PhotovoltaicPanel *panel, Grid *grid, Storage *storage);

};



#endif
