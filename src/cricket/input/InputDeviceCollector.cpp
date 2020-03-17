#include "InputDeviceCollector.h"

#include <cassert>

namespace
{
    //
    // A device map is invalid if it contains any null device mappings or
    // is empty.
    //
    bool 
    CheckDeviceMap(
        const cricket::InputDeviceCollector::DeviceMap& deviceMap
        )
    {
        if (deviceMap.empty()) { return false; }

        //
        // Gotta look up: std::if_any()
        //
        bool anyNullDevices{false};
        for (const auto& spDevice : deviceMap)
        {
            if (!spDevice) { anyNullDevices = true; break; }
        }

        return !anyNullDevices;
    }
}

namespace cricket
{
    InputDeviceCollectorPtr InputDeviceCollector::CreateAndInitialize(
            const DeviceMap& deviceMap
        )
    {
        InputDeviceCollectorPtr spCollector;
        if (!CheckDeviceMap(deviceMap))
        {
            return spCollector;
        }

        spCollector.reset(new InputDeviceCollector(deviceMap));
    }

    InputDeviceCollector::InputDeviceCollector(const DeviceMap& deviceMap)
        : m_deviceMap(deviceMap)
    {
        assert(CheckDeviceMap(deviceMap));
    }

    bool InputDeviceCollector::SetDeviceMap(const DeviceMap& deviceMap)
    {
        if (!CheckDeviceMap(deviceMap))
        {
            return false;
        }

        m_deviceMap = DeviceMap(std::begin(deviceMap), std::end(deviceMap));
        return true;
    }

    bool 
    InputDeviceCollector::GetActionStateForPlayer(
        ActionPlayer player,
        ActionState* pActionState
    )
    {
        const uint32_t PlayerIndex{ActionPlayerToIndex(player)};
        if (PlayerIndex == InvalidPlayerIndex)
        {
            return false;
        }

        *pActionState = m_deviceMap[PlayerIndex]->GetActionState();
        return true;
    }
}

