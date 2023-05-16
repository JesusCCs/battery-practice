#include <gmock/gmock.h>
#include "../../include/inverter.h"

class MockInverter : public Inverter {
public:
    MockInverter() = default;

    MOCK_METHOD(float, charge, (float powerToCharge));
    MOCK_METHOD(float, discharge, (float powerToDischarge));
};