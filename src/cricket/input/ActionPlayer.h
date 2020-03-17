//
// Represents the acting player.
//

#pragma once

#include <cstdint>

namespace cricket
{
    enum ActionPlayer
    {
        ActionPlayerUninitialized = 0,
        ActionPlayer1 = 1,
        ActionPlayer2 = 2,
        ActionPlayerMax
    };

    //
    // Returns (uint32_t)-1 if the player value is invalid.
    //
    static const uint32_t InvalidPlayerIndex{static_cast<uint32_t>(-1)};
    uint32_t ActionPlayerToIndex(ActionPlayer player);
}

