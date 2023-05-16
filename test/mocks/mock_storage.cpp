#include <gmock/gmock.h>
#include "../../include/storage.h"

class MockStorage : public Storage {
public:
    MockStorage() = default;

    MOCK_METHOD(float, charge, (float powerToCharge));
    MOCK_METHOD(float, discharge, (float powerToDischarge));
};