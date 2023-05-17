#include "../include/photovoltaic_panel.h"
#include "../include/house.h"
#include "../include/grid.h"
#include "../include/storage.h"
#include "../include/menu.h"

int main() {
    Menu menu;
    bool exit;

    do {

        menu.showIntro();

        auto photovoltaicPanel = menu.createPhotovoltaicPanel();

        auto house = menu.createHouse();

        auto grid = menu.createGrid();

        auto storage = menu.createStorage();

        storage->manageEnergyOf(house, photovoltaicPanel, grid);

        menu.showResults(house, photovoltaicPanel, grid, storage);

        exit = menu.showExit();

    } while (!exit);

    return 0;
}


