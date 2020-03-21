//
// Input device interface definition.
//

#pragma once

#include "InputDeviceClass.h"
#include "ActionState.h"

#include <memory>

namespace cricket
{
    class InputDevice
    {
    public:
        virtual ~InputDevice() = default;
        virtual InputDeviceClass::EnumType GetDeviceClass() = 0;
        virtual ActionState                GetActionState() = 0;
    };

    using InputDevicePtr = std::shared_ptr<InputDevice>;
}

