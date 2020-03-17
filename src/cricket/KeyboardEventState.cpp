#include "KeyboardEventState.h"

namespace cricket
{
    KeyboardEventState::KeyboardEventState()
        : m_actionState{} {}

    bool KeyboardEventState::ProcessEvent(const sf::Event& event)
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W)
            {
                m_actionState.MoveUp = true;
            }

            if (event.key.code == sf::Keyboard::S)
            {
                m_actionState.MoveDown = true;
            }

            if (event.key.code == sf::Keyboard::A)
            {
                m_actionState.MoveLeft = true;
            }

            if (event.key.code == sf::Keyboard::D)
            {
                m_actionState.MoveRight = true;
            }
        }
        else if(event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Q ||
                event.key.code == sf::Keyboard::Escape)
            {
                m_actionState.Quit = true;
            }

            if (event.key.code == sf::Keyboard::W)
            {
                m_actionState.MoveUp = false;
            }

            if (event.key.code == sf::Keyboard::S)
            {
                m_actionState.MoveDown = false;
            }

            if (event.key.code == sf::Keyboard::A)
            {
                m_actionState.MoveLeft = false;
            }

            if (event.key.code == sf::Keyboard::D)
            {
                m_actionState.MoveRight = false;
            }
        }
        else { return false; }

        return true;
    }

    const ActionState& KeyboardEventState::GetActionState() const
    {
        return m_actionState;
    }
}

