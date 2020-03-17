//
// Collects relevant inputs from devices which have been allocated to players.
//

#pragma once

#include <memory>
#include <vector>

#include "InputDevice.h"
#include "PlayerActionState.h"

namespace cricket
{
    // 
    // Forward decl
    //
    class InputDeviceCollector;
    using InputDeviceCollectorPtr = std::shared_ptr<InputDeviceCollector>;

    class InputDeviceCollector
    {
    public:
        //
        // The "Device map" here is just a vector where the indices correspond
        // to the player index (0 -> player 1, 1 -> player 2, etc.).
        //
        using DeviceMap = std::vector<InputDevicePtr>;
        static InputDeviceCollectorPtr CreateAndInitialize(
                const DeviceMap& deviceMap
            );
        ~InputDeviceCollector() = default;

        //
        // Fails if the device map is empty or invalid.
        //
        bool SetDeviceMap(const DeviceMap& deviceMap);
        
        //
        // Should only fail if the player identifier is invalid or out of
        // bounds.
        //
        bool 
        GetActionStateForPlayer(
            ActionPlayer player,
            ActionState* pActionState
            );

    private:
        InputDeviceCollector(
            const DeviceMap& deviceMap
            );

        //
        // Not copyable
        //
        InputDeviceCollector(const InputDeviceClass& other) = delete;
        InputDeviceCollector& operator=(const InputDeviceClass& other) = delete;

        DeviceMap m_deviceMap;
    };
}

