#include <gtest/gtest.h>
#include "../include/battery_module.h"

class BatteryModuleTest : public ::testing::Test {

protected:
    float maxPower = 100.0f;

    BatteryModule *batteryModule = new BatteryModule(maxPower, 12);

};

TEST_F(BatteryModuleTest, TestInitialMaxPower) {
    EXPECT_EQ(batteryModule->getMaxPower(), maxPower);
}

TEST_F(BatteryModuleTest, TestChargeInMaxPowerRange) {
    float powerToCharge = 50.0f;
    float expected = 0.0f;
    EXPECT_EQ(batteryModule->charge(powerToCharge), expected);
}

TEST_F(BatteryModuleTest, TestChargeInNotMaxPowerRange) {
    float powerToCharge = 120.0f;
    float expected = 20.0f;
    EXPECT_EQ(batteryModule->charge(powerToCharge), expected);
}

TEST_F(BatteryModuleTest, TestDischargeInMaxPowerRange) {
    float powerToDischarge = -50.0f;
    float expected = 0.0f;
    EXPECT_EQ(batteryModule->discharge(powerToDischarge), expected);
}

TEST_F(BatteryModuleTest, TestDischargeInNotMaxPowerRange) {
    float powerToDischarge = -120.0f;
    float expected = -20.0f;
    EXPECT_EQ(batteryModule->discharge(powerToDischarge), expected);
}

TEST_F(BatteryModuleTest, TestInvalidMaxPower) {
    EXPECT_THROW(BatteryModule(-50.0f, 12), std::invalid_argument);
}

TEST_F(BatteryModuleTest, TestInvalidChargePower) {
    EXPECT_THROW(batteryModule->charge(-50.0f), std::invalid_argument);
}

TEST_F(BatteryModuleTest, TestInvalidDischargePower) {
    EXPECT_THROW(batteryModule->discharge(50.0f), std::invalid_argument);
}

