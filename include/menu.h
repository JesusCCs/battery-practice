#ifndef MENU_H
#define MENU_H

#include "photovoltaic_panel.h"
#include "house.h"
#include "grid.h"
#include "storage.h"
#include "console.h"

class Menu {
private:

    bool onlyImportantParameters = false;

    int maxBatteries = 1;

    Console *console;

public:

    Menu();

    PhotovoltaicPanel *createPhotovoltaicPanel() const;

    House *createHouse() const;

    Grid *createGrid() const;

    Storage *createStorage() const;

    std::vector<BatteryModule *> *createBatteries() const;

    void showResults(House *house, PhotovoltaicPanel *panel, Grid *grid, Storage *storage) const;

    void showIntro();

    bool showExit() const;
};



#endif
