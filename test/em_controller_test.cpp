#include <gtest/gtest.h>
#include "../include/em_controller.h"
#include "mocks/mock_grid.cpp"
#include "mocks/mock_storage.cpp"
#include "mocks/mock_house.cpp"
#include "mocks/mock_photovoltaic_panel.cpp"

class EMControllerTest : public ::testing::Test {

protected:
    EMController *controller = new EMController();

    MockStorage *mockStorage = new MockStorage();

    MockGrid *mockGrid = new MockGrid();
    MockHouse *mockHouse = new MockHouse();
    MockPhotovoltaicPanel *mockPhotovoltaicPanel = new MockPhotovoltaicPanel();

    void SetUp() override {
        controller->setStorage(mockStorage);
    }

    void TearDown() override {
        delete controller;
        delete mockStorage;
        delete mockGrid;
        delete mockHouse;
        delete mockPhotovoltaicPanel;
    }

};

TEST_F(EMControllerTest, TestCallToCharge) {
    float powerProduction = 2000.0f;
    float powerConsumption = 1000.0f;
    float powerToSave = 500.0f;

    float powerSurplus = powerProduction - powerConsumption;

    float powerToGrid = powerSurplus - powerToSave;

    EXPECT_CALL(*mockHouse, getPowerConsumption()).Times(1).WillOnce(testing::Return(powerConsumption));
    EXPECT_CALL(*mockPhotovoltaicPanel, getPowerProduction()).Times(1).WillOnce(testing::Return(powerProduction));

    EXPECT_CALL(*mockStorage, charge(powerSurplus)).Times(1).WillOnce(testing::Return(powerToGrid));

    EXPECT_CALL(*mockGrid, updatePowerExchange(powerToGrid)).Times(1);

    controller->handle(mockHouse, mockPhotovoltaicPanel, mockGrid);
}

TEST_F(EMControllerTest, TestCallToDischarge) {
    float powerProduction = 1000.0f;
    float powerConsumption = 2000.0f;
    float powerToObtain = -500.0f;

    float powerNeed = powerProduction - powerConsumption;

    float powerFromGrid = powerNeed - powerToObtain;

    EXPECT_CALL(*mockHouse, getPowerConsumption()).Times(1).WillOnce(testing::Return(powerConsumption));
    EXPECT_CALL(*mockPhotovoltaicPanel, getPowerProduction()).Times(1).WillOnce(testing::Return(powerProduction));

    EXPECT_CALL(*mockStorage, discharge(powerNeed)).Times(1).WillOnce(testing::Return(powerFromGrid));

    EXPECT_CALL(*mockGrid, updatePowerExchange(powerFromGrid)).Times(1);

    controller->handle(mockHouse, mockPhotovoltaicPanel, mockGrid);
}

TEST_F(EMControllerTest, TestNoActionRequired) {
    float powerProduction = 1000.0f;
    float powerConsumption = 1000.0f;

    EXPECT_CALL(*mockHouse, getPowerConsumption()).Times(1).WillOnce(testing::Return(powerConsumption));
    EXPECT_CALL(*mockPhotovoltaicPanel, getPowerProduction()).Times(1).WillOnce(testing::Return(powerProduction));

    EXPECT_CALL(*mockStorage, discharge(testing::_)).Times(0);

    EXPECT_CALL(*mockGrid, updatePowerExchange(testing::_)).Times(0);

    controller->handle(mockHouse, mockPhotovoltaicPanel, mockGrid);
}

