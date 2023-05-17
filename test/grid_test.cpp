#include <gtest/gtest.h>
#include "../include/grid.h"

class GridTest : public ::testing::Test {

};

TEST_F(GridTest, TestUpdatePowerExchange) {
    float power = 50.0f;
    auto *grid = new Grid();

    grid->updatePowerExchange(power);

    EXPECT_EQ(grid->getPowerExchange(), power);

    power = -50.0f;

    grid->updatePowerExchange(power);

    EXPECT_EQ(grid->getPowerExchange(), 0);

    power = -10.0f;

    grid->updatePowerExchange(power);

    EXPECT_EQ(grid->getPowerExchange(), power);
}

TEST_F(GridTest, TestGetVoltage) {
    float voltage = 50.0f;

    auto grid = new Grid(voltage, 0.0f);

    EXPECT_EQ(grid->getVoltage(), voltage);
}

TEST_F(GridTest, TestGetFrequency) {
    float frequency = 50.0f;

    auto grid = new Grid(0.0f, frequency);

    EXPECT_EQ(grid->getFrequency(), frequency);
}