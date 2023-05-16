#include <gtest/gtest.h>
#include "../include/storage.h"
#include "mocks/mock_inverter.cpp"

class StorageTest : public ::testing::Test {

protected:
    Storage *storage = new Storage();

    MockInverter *mockInverter = new MockInverter();

    void SetUp() override {
        storage->setInverter(mockInverter);
    }

    void TearDown() override {
        delete storage;
        delete mockInverter;
    }
};

TEST_F(StorageTest, TestCallToCharge) {
    float powerToCharge = 50.0f;
    float powerNotAllocated = 10.0f;

    EXPECT_CALL(*mockInverter, charge(powerToCharge)).Times(1).WillOnce(testing::Return(powerNotAllocated));

    EXPECT_EQ(storage->charge(powerToCharge), powerNotAllocated);
}

TEST_F(StorageTest, TestCallToDischarge) {
    float powerToDischarge = -50.0f;
    float powerMissing = -10.0f;

    EXPECT_CALL(*mockInverter, discharge(powerToDischarge)).Times(1).WillOnce(testing::Return(powerMissing));

    EXPECT_EQ(storage->discharge(powerToDischarge), powerMissing);
}

TEST_F(StorageTest, TestInvalidChargePower) {
    EXPECT_THROW(storage->charge(-50.0f), std::invalid_argument);
}

TEST_F(StorageTest, TestInvalidDischargePower) {
    EXPECT_THROW(storage->discharge(50.0f), std::invalid_argument);
}
