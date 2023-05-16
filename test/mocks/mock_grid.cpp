#include <gmock/gmock.h>
#include "../../include/grid.h"

class MockGrid : public Grid {
public:
    MockGrid() = default;

    MOCK_METHOD(void, updatePowerExchange, (float powerToCharge));
};