//
// One keyboard to rule them all.
//
// Or something.
// 
// This file doesn't need a description, right?
//

#pragma once

#include "InputDevice.h"
#include "KeyboardEventState.h"

namespace cricket
{
    class KeyboardInputDevice : public InputDevice
    {
    public:
        KeyboardInputDevice(KeyboardEventState& keyboardEventState);

        InputDeviceClass::EnumType GetDeviceClass() override;
        ActionState                GetActionState() override;

    private:
        KeyboardEventState& m_keyboardEventState;
    };
}

