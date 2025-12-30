#include <demo/test_switch.h>

import <format>;
import <iostream>;

namespace demo {

void RunTestSwitch()
{
    using namespace std;

    enum class Mode { Default, Custom, Standard };
    int value{ 42 };
    Mode mode{ Mode::Custom };

    switch (mode) {
        using enum Mode;
        case Custom:
            value = 84;
            cout << format("Custom mode: value={}\n", value);
            [[fallthrough]];
        case Standard:
            value = 21;
            cout << format("Standard mode: value={}\n", value);
            [[fallthrough]];
        case Default:
            value = 42;
            cout << format("Default mode: value={}\n", value);
            break;
    }
}

} // namespace demo
