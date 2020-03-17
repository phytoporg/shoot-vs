#pragma once

#include "ActionPlayer.h"
#include "ActionState.h"
#include <cstdint>

namespace cricket
{
    struct PlayerActionState
    {
        PlayerActionState(
            ActionPlayer player,
            ActionState state,
            uint32_t frameNumber) : 
                Player(player), State(state), FrameNumber(frameNumber) {}

        //
        // The player performing the action.
        //
        ActionPlayer Player;

        //
        // Representation of the state to be performed.
        //
        ActionState  State;

        //
        // The frame number at which to execute the action.
        //
        uint32_t     FrameNumber;
    };
}

