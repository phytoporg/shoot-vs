//
// Facilitates input device discovery.
//
// For now, we assume that a keyboard is always present.
//

#pragma once

#include "InputDevice.h"
#include "KeyboardEventState.h"

#include <vector>

namespace cricket
{
    class InputDeviceEnumerator
    {
    public:
        //
        // Again, we're assuming that a keyboard is always present. Cricket
        // is working against SFML, which surfaces keyboard events via a window
        // class' event pump.
        //
        // We have to empty the window event queue at a high level in the
        // game loop because there are events to handle which are not input
        // related, so this injects that mechanism to the bottom of the input
        // stack (keyboardEventState will be injected into the keyboard device
        // instance).
        //
        InputDeviceEnumerator(KeyboardEventState& keyboardEventState);

        std::vector<InputDevicePtr> GetAvailableDevices();

    private:
        InputDevicePtr      m_spKeyboardDevice;
    };
}

