//
// Input device interface definition.
//

#pragma once

#include "InputDeviceClass.h"
#include "ActionState.h"

namespace cricket
{
    class InputDevice
    {
    public:
        virtual ~InputDevice() = default;
        virtual InputDeviceClass GetDeviceClass() = 0;
        virtual ActionState      GetActionState() = 0;
    };
}

