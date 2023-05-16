cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 11)

project(sonnen_batterie)

add_subdirectory(test)

add_executable(sonnen_batterie src/main.cpp src/models/photovoltaic_panel.cpp include/photovoltaic_panel.h src/models/grid.cpp include/grid.h src/models/house.cpp include/house.h src/models/inverter.cpp include/inverter.h src/models/battery_module.cpp include/battery_module.h src/models/storage.cpp include/storage.h src/models/em_controller.cpp include/em_controller.h src/services/console.cpp include/console.h)
