cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 11)

project(sonnen_batterie_test)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_library(
        src
        ../src/models/battery_module.cpp
        ../src/models/inverter.cpp
        ../src/models/em_controller.cpp
        ../src/models/grid.cpp
        ../src/models/house.cpp
        ../src/models/photovoltaic_panel.cpp
        ../src/models/storage.cpp
)

add_executable(
        test_run
        battery_module_test.cpp
        inverter_test.cpp
        em_controller_test.cpp
        storage_test.cpp
        mocks/mock_grid.cpp
        mocks/mock_house.cpp
        mocks/mock_photovoltaic_panel.cpp
        mocks/mock_storage.cpp
        grid_test.cpp house_test.cpp photovoltaic_panel_test.cpp console_test.cpp)

target_link_libraries(test_run gtest gtest_main)
target_link_libraries(test_run gmock gmock_main)

target_link_libraries(test_run src)
