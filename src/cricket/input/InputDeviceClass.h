//
// Enum to identify device types.
//

#pragma once

namespace cricket
{
    struct InputDeviceClass
    {
        enum EnumType
        {
            Uninitialized = 0,
            Keyboard,
            Network,
            Controller
        };
    };
}

