#include "ActionPlayer.h"

namespace cricket
{
    //const uint32_t InvalidPlayerIndex{static_cast<uint32_t>(-1)};
    uint32_t ActionPlayerToIndex(ActionPlayer player)
    {
        if (player <= ActionPlayerUninitialized || 
            player >= ActionPlayerMax)
        {
            return InvalidPlayerIndex;
        }

        return static_cast<uint32_t>(player) - 1;
    }
}

