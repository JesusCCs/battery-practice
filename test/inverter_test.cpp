#include <gtest/gtest.h>
#include "../include/inverter.h"

class InverterTest : public ::testing::Test {

protected:
    std::vector<BatteryModule *> *batteries = new std::vector<BatteryModule *>();

    float maxPowerToExchange = 100.0f;

    void SetUp() override {
        batteries->push_back(new BatteryModule(100.0f, 12));
        batteries->push_back(new BatteryModule(150.0f, 12));
        batteries->push_back(new BatteryModule(100.0f, 12));
    }

    void TearDown() override {
        for (auto battery: *batteries) {
            delete battery;
        }

        batteries->clear();
    }

    float totalBatteryPower() {
        float totalPower = 0.0f;

        for (auto battery: *batteries) {
            totalPower += battery->getMaxPower();
        }

        return totalPower;
    }

};

TEST_F(InverterTest, TestFullChargeWithoutLimitInInverter) {
    auto totalPower = totalBatteryPower();

    auto inverter = new Inverter(totalPower, batteries);

    float expected = 0.0f;

    EXPECT_EQ(inverter->charge(totalPower), expected);
    EXPECT_EQ(inverter->getInverterPower(), totalPower);
}

TEST_F(InverterTest, TestFullChargeWithLimitInInverter) {
    auto inverter = new Inverter(maxPowerToExchange, batteries);

    auto powerToCharge = totalBatteryPower();

    auto expected = powerToCharge - maxPowerToExchange;

    EXPECT_EQ(inverter->charge(powerToCharge), expected);
    EXPECT_EQ(inverter->getInverterPower(), maxPowerToExchange);
}

TEST_F(InverterTest, TestFullChargeWithLimitInBatteries) {
    float batteriesTotalPower = totalBatteryPower();
    float differenceBetweenBatteriesAndInverter = 1.0f;
    float inverterMaxPower = batteriesTotalPower + differenceBetweenBatteriesAndInverter;

    auto inverter = new Inverter(inverterMaxPower, batteries);

    EXPECT_EQ(inverter->charge(inverterMaxPower), differenceBetweenBatteriesAndInverter);
    EXPECT_EQ(inverter->getInverterPower(), batteriesTotalPower);
}

TEST_F(InverterTest, TestPartialCharge) {
    auto inverter = new Inverter(maxPowerToExchange, batteries);

    float toCharge = 50.0f;
    float expected = 0.0f;

    EXPECT_EQ(inverter->charge(toCharge), expected);
    EXPECT_EQ(inverter->getInverterPower(), toCharge);
}

TEST_F(InverterTest, TestChargeWithInverterChargingInMaximunCapacity) {
    auto inverter = new Inverter(maxPowerToExchange, maxPowerToExchange, batteries);

    float toCharge = 50.0f;

    EXPECT_EQ(inverter->charge(toCharge), toCharge);
    EXPECT_EQ(inverter->getInverterPower(), maxPowerToExchange);
}

TEST_F(InverterTest, TestChargeWithInverterChargingPartialCapacity) {
    float toCharge = 150.0f;

    float powerCharging = maxPowerToExchange * 0.5f;

    float powerNotAllocated = toCharge - powerCharging;

    auto inverter = new Inverter(maxPowerToExchange, powerCharging, batteries);

    EXPECT_EQ(inverter->charge(toCharge), powerNotAllocated);
    EXPECT_EQ(inverter->getInverterPower(), maxPowerToExchange);
}

TEST_F(InverterTest, TestFullDischargeWithoutLimitInInverter) {
    auto maxPowerToExchange = totalBatteryPower();

    auto inverter = new Inverter(maxPowerToExchange, batteries);

    auto powerToDischarge = -totalBatteryPower();

    float expectedToNotDischarge = 0.0f;

    EXPECT_EQ(inverter->discharge(powerToDischarge), expectedToNotDischarge);
    EXPECT_EQ(inverter->getInverterPower(), powerToDischarge);
}

TEST_F(InverterTest, TestFullDischargeWithLimitInInverter) {
    auto inverter = new Inverter(maxPowerToExchange, batteries);

    auto powerToDischarge = -totalBatteryPower();

    auto maxPowerExpectedToDischarge = - maxPowerToExchange;

    auto expectedToNotDischarge = powerToDischarge - maxPowerExpectedToDischarge;

    EXPECT_EQ(inverter->discharge(powerToDischarge), expectedToNotDischarge);
    EXPECT_EQ(inverter->getInverterPower(), maxPowerExpectedToDischarge);
}

TEST_F(InverterTest, TestFullDischargeWithLimitInBatteries) {
    float batteriesTotalPower = totalBatteryPower();
    float differenceBetweenBatteriesAndInverter = 1.0f;
    float inverterMaxPower = batteriesTotalPower + differenceBetweenBatteriesAndInverter;

    auto inverter = new Inverter(inverterMaxPower, batteries);

    EXPECT_EQ(inverter->discharge(-inverterMaxPower), -differenceBetweenBatteriesAndInverter);
    EXPECT_EQ(inverter->getInverterPower(), -batteriesTotalPower);
}

TEST_F(InverterTest, TestPartialDischarge) {
    auto inverter = new Inverter(maxPowerToExchange, batteries);

    float toDischarge = -50.0f;
    float expectedNotDischarge = 0.0f;

    EXPECT_EQ(inverter->discharge(toDischarge), expectedNotDischarge);
    EXPECT_EQ(inverter->getInverterPower(), toDischarge);
}

TEST_F(InverterTest, TestDischargeWithInverterDishargingInMaximunCapacity) {
    auto inverter = new Inverter(maxPowerToExchange, -maxPowerToExchange, batteries);

    float toDischarge = -50.0f;

    EXPECT_EQ(inverter->discharge(toDischarge), toDischarge);
    EXPECT_EQ(inverter->getInverterPower(), -maxPowerToExchange);
}

TEST_F(InverterTest, TestDischargeWithInverterChargingPartialCapacity) {
    float toDischarge = -150.0f;

    float powerDischarging = - maxPowerToExchange * 0.5f;

    float powerNotDischarged = toDischarge - powerDischarging;

    auto inverter = new Inverter(maxPowerToExchange, powerDischarging, batteries);

    EXPECT_EQ(inverter->discharge(toDischarge), powerNotDischarged);
    EXPECT_EQ(inverter->getInverterPower(), - maxPowerToExchange);
}

TEST_F(InverterTest, TestInvalidMaxPower) {
    EXPECT_THROW(Inverter(-10, batteries), std::invalid_argument);
}

TEST_F(InverterTest, TestInvalidNegativeChargePower) {
    auto inverter = new Inverter(maxPowerToExchange, batteries);

    EXPECT_THROW(inverter->charge(-10.0f), std::invalid_argument);
}

TEST_F(InverterTest, TestInvalidPositiveDischargePower) {
    auto inverter = new Inverter(maxPowerToExchange, batteries);

    EXPECT_THROW(inverter->discharge(10.0f), std::invalid_argument);
}
