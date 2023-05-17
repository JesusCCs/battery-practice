#include <gtest/gtest.h>
#include "../include/house.h"

class HouseTest : public ::testing::Test {

};

TEST_F(HouseTest, TestGetSetPowerConsumption) {
    auto house = new House(250, 50);

    EXPECT_EQ(house->getPowerConsumption(), 0);

    house->setPowerConsumption(50);

    EXPECT_EQ(house->getPowerConsumption(), 50);
}

