#include <gtest/gtest.h>
#include "../include/photovoltaic_panel.h"

class PhotovoltaicPanelTest : public ::testing::Test {

};

TEST_F(PhotovoltaicPanelTest, TestGetSetPowerProduction) {
    auto photovoltaicPanel = new PhotovoltaicPanel(250, 50);

    EXPECT_EQ(photovoltaicPanel->getPowerProduction(), 250);

    photovoltaicPanel->setPowerProduction(50);

    EXPECT_EQ(photovoltaicPanel->getPowerProduction(), 50);
}

TEST_F(PhotovoltaicPanelTest, TestGetSetVoltageProduction) {
    auto photovoltaicPanel = new PhotovoltaicPanel(250, 50);

    EXPECT_EQ(photovoltaicPanel->getVoltageProduction(), 50);

    photovoltaicPanel->setVoltageProduction(250);

    EXPECT_EQ(photovoltaicPanel->getVoltageProduction(), 250);
}

TEST_F(PhotovoltaicPanelTest, TestGetSetCurrentProduction) {
    auto photovoltaicPanel = new PhotovoltaicPanel(250, 50);

    EXPECT_EQ(photovoltaicPanel->getCurrentProduction(), 5);

    photovoltaicPanel->setCurrentProduction(10);

    EXPECT_EQ(photovoltaicPanel->getCurrentProduction(), 10);
}