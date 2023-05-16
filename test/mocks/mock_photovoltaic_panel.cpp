#include <gmock/gmock.h>
#include "../../include/photovoltaic_panel.h"

class MockPhotovoltaicPanel : public PhotovoltaicPanel {
public:
    MockPhotovoltaicPanel() = default;

    MOCK_METHOD(float, getPowerProduction, ());
};
