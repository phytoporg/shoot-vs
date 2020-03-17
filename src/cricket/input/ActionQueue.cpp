#include "input/ActionQueue.h"
#include "ActionPlayer.h"
#include "ActionState.h"

namespace cricket
{
    void 
    ActionQueue::Enqueue(
        ActionPlayer player,
        ActionState actionState,
        uint32_t actionFrame
        )
    {
        m_actionSet.insert({player, actionState, actionFrame});
    }

    bool ActionQueue::PeekEarliestFrame(uint32_t* pFrameNum) const
    {
        if (m_actionSet.empty()) { return false; }

        *pFrameNum = m_actionSet.rbegin()->FrameNumber;
        return true;
    }

    bool ActionQueue::GetAndRemoveActionsOnFrame(
        uint32_t actionFrame,
        std::vector<PlayerActionState>* pPlayerActionStates)
    {
        if (m_actionSet.empty()) { return false; }
        pPlayerActionStates->clear();

        const ActionState DummyActionState = {};
        PlayerActionState QueryState = {
            ActionPlayer1,    // Arbitrary
            DummyActionState, // Arbitrary
            actionFrame       // This is the value that matters
        };
        const auto RangeIterators = m_actionSet.equal_range(QueryState);
        if (RangeIterators.first == RangeIterators.second) { return false; }

        *pPlayerActionStates = std::vector<PlayerActionState>(
            RangeIterators.first, RangeIterators.second
            );
        m_actionSet.erase(RangeIterators.first, RangeIterators.second);
        return true;
    }
}

