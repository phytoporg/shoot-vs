//
// Helper class for processing sfml keyboard inputs. Static keyboard mapping
// for now.
//

#include <SFML/Window/Event.hpp>

#include "ActionState.h"

#pragma once

namespace cricket
{
    class KeyboardEventState
    {
    public:
        KeyboardEventState();

        //
        // Returns false if the provided event is not a keyboard event.
        //
        bool ProcessEvent(const sf::Event& event);

        const ActionState& GetActionState() const;

    private:
        ActionState m_actionState;
    };
}

