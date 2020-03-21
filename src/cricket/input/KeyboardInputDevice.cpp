#include "KeyboardInputDevice.h"

namespace cricket
{
    KeyboardInputDevice::KeyboardInputDevice(
        KeyboardEventState& keyboardEventState
        ) : m_keyboardEventState(keyboardEventState)
    {}

    InputDeviceClass::EnumType KeyboardInputDevice::GetDeviceClass()
    {
        return InputDeviceClass::Keyboard;
    }

    ActionState KeyboardInputDevice::GetActionState()
    {
        return m_keyboardEventState.GetActionState();
    }
}

