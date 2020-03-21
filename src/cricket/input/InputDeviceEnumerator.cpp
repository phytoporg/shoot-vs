#include "InputDeviceEnumerator.h"
#include "KeyboardInputDevice.h"

namespace cricket
{
    InputDeviceEnumerator::InputDeviceEnumerator(
        KeyboardEventState& keyboardEventState
        ) 
    {
        m_spKeyboardDevice.reset(new KeyboardInputDevice(keyboardEventState));
    }

    std::vector<InputDevicePtr> InputDeviceEnumerator::GetAvailableDevices()
    {
        //
        // TODO: Support for additional device class enumeration.
        //
        return std::vector<InputDevicePtr> { m_spKeyboardDevice };
    }
}
