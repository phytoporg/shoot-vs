//
// Light wrapper around priority queue which ties player, action and action 
// frames together for delayed and rollback processing.
//

#pragma once

#include "ActionState.h"
#include "ActionPlayer.h"
#include "PlayerActionState.h"

#include <cstdint>
#include <set>
#include <vector>

namespace cricket
{
    class ActionQueue
    {
    public:

        ActionQueue() = default;

        //
        // Add an action state to the queue, prioritized by the desired frame.
        //
        void 
        Enqueue(
            ActionPlayer player,
            ActionState actionState,
            uint32_t actionFrame);

        //
        // Peek the earliest frame # in the priority queue.
        //
        bool PeekEarliestFrame(uint32_t* pFrameNum) const;

        //
        // Grab all player actions which match a particular action frame # and
        // remove them from the data structure.
        //
        bool GetAndRemoveActionsOnFrame(
            uint32_t actionFrame,
            std::vector<PlayerActionState>* pPlayerActionStates);

    private:
        struct PlayerActionCmp
        {
            bool operator()(
                const PlayerActionState& a,
                const PlayerActionState& b) const
            {
                return a.FrameNumber > b.FrameNumber;
            }
        };

        std::multiset<PlayerActionState, PlayerActionCmp> m_actionSet;
    };
}

