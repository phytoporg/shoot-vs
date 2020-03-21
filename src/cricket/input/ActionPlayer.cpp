#include "ActionPlayer.h"

namespace cricket
{
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

