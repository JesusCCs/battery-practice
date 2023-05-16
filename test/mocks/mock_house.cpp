#include <gmock/gmock.h>
#include "../../include/house.h"

class MockHouse : public House {
public:
    MockHouse() = default;

    MOCK_METHOD(float, getPowerConsumption, ());
};
